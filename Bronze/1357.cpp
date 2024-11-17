// Generated with https://github.com/boj-rs/basm-rs
// Learn rust (https://doc.rust-lang.org/book/) and get high performance out of the box!

// SOLUTION BEGIN
/*
use alloc::vec::Vec;
use basm::platform::is_local_env;
use basm::platform::io::{Reader, ReaderTrait, Writer, Print};
use basm_macro::basm_export;
use crate::alloc::string::{*};

fn reverse_number(n: u32) -> u32 {
    n.to_string().chars().rev().collect::<String>().parse::<u32>().unwrap()
}

pub fn main() {
    let mut reader: Reader = Default::default();
    let mut writer: Writer = Default::default();
    let x = reader.u32();
    let y = reader.u32();
    let xx = reverse_number(x);
    let yy = reverse_number(y);
    writer.u32(reverse_number(xx+yy));
}
*/
// SOLUTION END

// LOADER BEGIN
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <io.h>
#elif defined(__linux__)
#include <unistd.h>
#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS 0x20
#endif
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif
#ifdef DEBUG
#include <stdio.h>
#endif

#ifndef UINT32_MAX
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
#endif

// Use cdecl on x86 (32bit), Microsoft x64 calling convention on amd64 (64bit)
#if defined(__LP64__) // LP64 machine, OS X or Linux
#define BASMCALL __attribute__((ms_abi))
#elif defined(_WIN64) // LLP64 machine, Windows
#if defined(_MSC_VER)
#define BASMCALL
#else
#define BASMCALL __attribute__((ms_abi))
#endif
#else // 32-bit machine, Windows or Linux or OS X -> forbid compilation
#error "The current file can only be compiled for amd64."
#define BASMCALL
#endif

// Base85 decoder. Code adapted from:
//     https://github.com/rafagafe/base85/blob/master/base85.c
const char *b85 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>\?@^_`{|}~";
void b85tobin(void *dest, char const *src) {
    uint32_t *p = (uint32_t *)dest;
    uint8_t digittobin[256];
    for (uint8_t i=0; i<85; i++) digittobin[(uint8_t)b85[i]] = i;
    while (1) {
        while (*src == '\0') src++;
        if (*src == ']') break;
        uint32_t value = 0;
        for (uint32_t i=0; i<5; i++) {
            value *= 85;
            value += digittobin[(uint8_t)*src++];
        }
        *p++ = (value >> 24) | ((value >> 8) & 0xff00) | ((value << 8) & 0xff0000) | (value << 24);
    }
}

#pragma pack(push, 1)
typedef struct {
    uint64_t    env_id;
    uint64_t    env_flags;
    uint64_t    win_kernel32;       // handle of kernel32.dll
    uint64_t    win_GetProcAddress; // pointer to kernel32!GetProcAddress
    void       *ptr_alloc_rwx;      // pointer to function
    void       *ptr_alloc;          // pointer to function
    void       *ptr_alloc_zeroed;   // pointer to function
    void       *ptr_dealloc;        // pointer to function
    void       *ptr_realloc;        // pointer to function
    void       *ptr_read_stdio;     // pointer to function
    void       *ptr_write_stdio;    // pointer to function
} PLATFORM_DATA;
#pragma pack(pop)

#define ENV_ID_UNKNOWN              0
#define ENV_ID_WINDOWS              1
#define ENV_ID_LINUX                2
#define ENV_ID_WASM                 3
#define ENV_ID_MACOS                4
#define ENV_FLAGS_LINUX_STYLE_CHKSTK    0x0001  // disables __chkstk in binaries compiled with Windows target
#define ENV_FLAGS_NATIVE                0x0002  // indicates the binary is running without the loader
#define ENV_FLAGS_NO_EXIT               0x0004  // do not call SYS_exitgroup on Linux (support fn-impl scenarios)

#if !defined(_WIN32) && !defined(__linux__)
BASMCALL void *svc_alloc(size_t size, size_t align) {
    return malloc(size);
}
BASMCALL void *svc_alloc_zeroed(size_t size, size_t align) {
    return calloc(1, size);
}
BASMCALL void svc_free(void *ptr, size_t size, size_t align) {
    free(ptr);
}
BASMCALL void *svc_realloc(void* memblock, size_t old_size, size_t old_align, size_t new_size) {
    // This won't be called in loader stub.
    // Also, the main executable will directly call OS APIs/syscalls
    return realloc(memblock, new_size);
}
BASMCALL size_t svc_read_stdio(size_t fd, void *buf, size_t count) {
    if (fd != 0) return 0;
    return fread(buf, 1, count, stdin);
}
BASMCALL size_t svc_write_stdio(size_t fd, void *buf, size_t count) {
    if (fd != 1 && fd != 2) return 0;
    return fwrite(buf, 1, count, (fd == 1) ? stdout : stderr);
}
#endif

BASMCALL void *svc_alloc_rwx(size_t size) {
#ifdef _WIN32
    size_t ret = (size_t) VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
#else
    size_t ret = (size_t) syscall(9, NULL, size, 0x7, 0x22, -1, 0);
    if (ret == (size_t)-1) ret = 0;
#endif
    return (void *) ret;
}

typedef int (BASMCALL *stub_ptr)(void *, void *);

#define STUB_RAW "\x57\x56\x53\x41\x54\x41\x55\x41\x56\x41\x57\xc8\x28\x00\x00\x52\x5e\x51\x5b\x31\xc0\xac\x49\x89\xc5\xac\x49\x89\xc6\xac\x49\x89\xc7\xac\x89\xc1\xb0\x03\xd3\xe0\x05\x00\x08\x00\x00\x49\x94\xad\x91\xff\x53\x20\x50\x49\x91\xad\x49\x89\xf0\x96\x53\x55\x48\x8d\x7c\x24\xfe\x4c\x29\xe4\x4c\x29\xe4\x44\x89\xe1\x66\xb8\x00\x04\xfd\xf3\x66\xab\xfc\x54\x5d\x83\xc8\xff\x48\x83\xc0\x02\x50\x50\x56\x6a\xff\x51\x93\xe8\x49\x00\x00\x00\x52\xe8\x2e\x00\x00\x00\x0f\xb7\x44\x75\x00\x8b\x55\xe4\xc1\xea\x0b\x0f\xaf\xd0\x29\x55\xe4\x29\x55\xe8\x73\x0c\x89\x55\xe4\x01\x55\xe8\x99\x2d\xe1\x07\x00\x00\xc1\xe8\x05\x66\x29\x44\x75\x00\xf7\xda\x5a\xc3\x80\x7d\xe7\x00\x75\x0e\x48\xc1\x65\xe4\x08\x41\x8a\x00\x49\xff\xc0\x88\x45\xe8\xc3\x5f\x4c\x89\xc9\x44\x88\xf0\x88\xc7\x5e\x56\x20\xcf\x44\x21\xe9\xc1\xe6\x05\x8d\x74\x4e\x40\xff\xd7\x99\x58\x72\x46\x44\x89\xf9\xd3\xe3\xb3\x00\x8d\x8c\x5b\x00\x08\x00\x00\x8d\x5a\x01\x04\xfd\x18\xd2\x20\xd0\x3c\x07\x73\xf6\x50\x3c\x04\x72\x10\xb7\x01\x8b\x45\xfc\x48\xf7\xd8\x41\x32\x14\x01\x30\xde\x20\xf7\xd1\xe2\x89\xde\x21\xd6\x01\xde\x01\xce\xff\xd7\x10\xdb\x73\xec\x99\xe9\x03\x01\x00\x00\x89\xf3\x8d\x74\x82\x10\x04\xf9\x18\xc0\x24\x03\x50\xff\xd7\x72\x0c\x0f\x10\x45\xf0\x0f\x11\x45\xec\xb2\x5b\xeb\x32\xff\xc6\xff\xd7\x72\x10\x8d\x73\x01\xff\xd7\x72\x1f\x83\x4d\xd8\x09\xe9\xc5\x00\x00\x00\xb2\x03\x8b\x5d\xfc\xff\xc6\xff\xca\x87\x5c\x95\xf0\x74\x04\xff\xd7\x72\xf2\x89\x5d\xfc\x83\x4d\xd8\x08\xb2\x94\x8d\x34\xd2\x99\xff\xd7\xff\xc6\x8d\x1c\xce\xb1\x03\x73\x11\xb2\x01\xff\xd7\x73\x08\x8d\x5e\x7f\xb1\x08\x83\xc2\xe2\x83\xeb\x80\x6a\x01\x5e\x56\x56\x01\xde\xff\xd7\x5e\x11\xf6\xe2\xf6\x8d\x5c\xd6\xf9\x83\x7d\xd8\x04\x5a\x53\x73\x6e\x83\x45\xd8\x07\x83\xeb\x04\x19\xc0\x21\xc3\x8d\x5c\xda\x4f\x52\x8d\x34\xda\xff\xd7\x11\xd2\x89\xd1\x83\xe9\x40\x72\xf2\x5b\x83\xf9\x04\x72\x43\x89\xde\xd1\xe9\xd3\xd3\xff\xc9\xf6\xd2\xb6\x02\x01\xda\x83\xf9\x06\x72\x1e\xff\xc9\xe8\xc1\xfe\xff\xff\xd1\x6d\xe4\x8b\x55\xe4\x39\x55\xe8\x72\x06\x29\x55\xe8\x0f\xab\xcb\x83\xf9\x04\x75\xe3\x99\x56\x01\xd6\xff\xd7\x5e\x11\xf6\xe2\xf6\x11\xc9\xd1\xee\x75\xfa\x01\xd9\xff\xc1\x89\x4d\xfc\x74\x1b\x5a\x8b\x4d\xfc\x48\xf7\xd9\x41\x0f\xb6\x1c\x09\x41\x88\x19\x49\xff\xc1\xff\xca\x79\xeb\xe9\x8c\xfe\xff\xff\x4a\x8d\x64\x64\x30\x5d\x59\x58\x49\x03\x41\xf8\xff\xd0\xc9\x41\x5f\x41\x5e\x41\x5d\x41\x5c\x5b\x5e\x5f\xc3\x00"
#if defined(__GNUC__)
__attribute__ ((section (".text#"))) const char stub_raw[] = STUB_RAW;
stub_ptr get_stub() {
    return (stub_ptr) stub_raw;
}
#else
const char stub_raw[] = STUB_RAW;
stub_ptr get_stub() {
    char *stub = (char *) svc_alloc_rwx(4096);
    for (size_t i = 0; i < sizeof(stub_raw); i++) stub[i] = stub_raw[i];
    return (stub_ptr) stub;
}
#endif
char payload[][4096] = {
"00008QBnW^^tNsQ&<PSAb3yfHveH0Vc%6f^UJrk$pyoe&Hp-sYM~~R(KFl%6K4`F\?{l`vp07QcB8>HyH$&bmHO@sU!3cY;Rrs)mjO6R89T=C%CbfoC5NA<!%Aoz=@g84rjlD`oOw!NKDnn535(Nkc@5(JJR_E+=o!pk1l74-sb+c;*Ry&KSRoT#pXvUXmMlY)>tsK5x|!DNTK$1c4M3gNN}!6PM1y8NA<QFl<WeWtia#!K;&d(CDJ`-P~3nVvum3NtK|Q*ktg&y&q)\?qYJPF7YloZ%RQSdo-<cnhCDMy9yE>_mrX3NE0)nV4p6X%s5YFph{t~jT_^7MF`=LK^@=wPs{|HCJI$+`Ksx)eu~{oY>*)h%cNx)iH2A<h-S\?kgaU3h298QcQDxX(9DJfSjJ*qrFuV806l-pofZgSI7~0ZzmDsHp)jT>qUHBCf3^%HkUsiKMV^pW5+po~\?LkB;9_fcs|`CrCi*D||ujFH$BL>erqi!$R}6F9e!d$uo)Mc8jhmaS;EYH`Z|TtkzL0T;&_s;CV+cWXyanig<wExEbpEIu4`{1b\?krhYZkX4a5_N;u{uU5Mof*xjHq^GfZ>-|@KQ;RC0AM;-S584``=bwb(!#5RIS\?w+89O~l+l0|i)pk%4k@T%|)JL%b3&mE*8Fa;icc\?HRVk%(<)J3NM-H&z{O~q3WD;@l<9F{yOsf@({407|tEx!cbfSeEM9OhowX\?QdRrN8kM7skJ(|WHzp&(f#A!S``=sVarQ6CSkk{xjn}0eES-7<wgUO=LuE}\?;PGWcUZNl%G$*GpTC&*D!VI!KGEM^m6r69g&tzLMl`X`xSp96W6-uj7_Fbt\?Ol)ziQ2roSZoM$ML%sa~8-n*f{t8qdX%C\?|M2kcXx+NsA67w_fH)Hjmjg9EdLxxaSuY3HvOO7dBX%WOa&HwGyIE1;\?7nt53;lKmgT^W`*NY7K1H@kOYTJQk{=2Qh$nwdB(A3X1Y+WKjQ0\?m1bkKn4V3+OZ3Nqt`M6FT};R`vchYsE\?_mfiM-RV-e`!)lptXlhD$ktNzTTRS)9U12KmJ%m5}fp7t-+8FOhNyB~yteguEuLW-;N-2ipd=CZ6;+yLQuONfP#a@9hhpz\?$qFsd2Ehw6wCyJ|mBiCRA`{KfbD+-u^Se%lg\?uqrc<4e`GGwVwF=;OawtZ(+dh)kwidCuxJ9)FF^6AnZAD1T2=({Zxzi~fLB#kR;-!$#%\?tceawPs5A`AUo!rU+tWN\?NqFaEcl}XPSf6eI%YMNT-EFpkFazTwQVXb)XF^HVvkdqX1N=^f=CYPJPr*cS1`-1i5fx4ZM)Sf)T@GnG9Dq;<7\?}QgMpMKQSt>j$*$ij;}{sm2GG)X9v\?3I^+JX5I=\?VG;NW95nshFnR\?(<(l1_8KBBMDE\?DsFeTa3Yyd79j+-6m$GMYGAy_DX=FB}9^%ma7CK1SgRrT~=a!$V9W\?HnzrO;%1|Hy-Pt<cV(+{fX%F28)7F$lj%4>d3eb3=YpgA>}WHy-+t3QC6=JTF65A<-)RlErm6\?Y+{szifR{Mk)!gM;0Sks36>\?<INP!igH=*(UC<{+aG2sw!MyGesSl1s~PRt!fVLfVz){;&E*N<ar\?)t1Pdy!hO>LxW56dTW|3sG*{rZBFib@e2%TDg5YKk#&E+ZMhlIMF5Obw9lm(Z(n*LpsP=B$E\?^K9VLbyin@T1Wta-|EvP<ma|N~n(S-Z;kOIwz*dE6AxX1=sfJr@0D;M-MCgxfQr7j^%n1&sSMfkiB-=tbuMEP4|9oMAh=ry>zQ2W``%m1V@FjGKV(UcLmt-}o@d{F#)HmIQS<HL&Dl`0)_2a0B6s_=m7C`yW3g<0uvgM3L9^YCHcmd_R&iMoB\?uO^cY6x=id6B@^;E<SNUa(e0b\?a<HUG!YKxv=XJIWnK6F#$XYocM16=c`_(BQO8kOxz=;F=7E>Da|f;k113W+zC9c^Mm@KK_{y5<%O8#1x8xmL8nU3khJ$eY7%=bk5bk%O9+V)5m6k_{DGm=H*$\?aSwN~P>PDG28EOE+*7L$WSg6z;z$m^>xUIaw2c-_2_2O6XB0gXRKl0JZ<_s#8T>tu_4{kIP{j|{iL#-4`xmbabe1KdSw*n)X^ZWt5L939dC@SA}gR6R<wAMOJ6FX0$cXurPcZNHHx$a!rd!@\?nr\?H\?5^B;2n#_|BuWr(Pb{LYQ^Zf6sddI6<9fY&B+Icp^N%$pOcy2PO*UpnG\?;=tNGDNZ(q{SJQndzTB%ztvB_lv=3h2862$occ+)mS(75ZEQAF4iqTrJ(XgEPGx8ShjrqKRtj>U+^+(^5;V=5y%>B_(Sra\?*QarPh$IpKtY^82ux3uuS8#24+e@yiv|5m08&6moU$GWKtcG#V6=t@WuujQpUx`g(b3`YOw8`RA6R=z!fGXPTtZ|j(<F&HmS)bZQ$kABr^V@T^xM|(rm4E&Z1I*T&%e\?2u*ZhzOI+i78^m~KqW^X^&sb{a4``qHT4q6e&eLi17R01Eq8W6fRmb@u%kNV_gA0!@p-f(~R$^T%ONbjP1zYA}Mus3TU<dCix)-z8BYRPelEh6_hfk1*!^HRJ6%B*wmHnC;tH1b}jp!2YH@v7Cg#IUFfKh_b75=-Ax_WeZcP|&LJ8Y2!rIj6sd{v19ZPj$SX$OsAY-MQ%o!R3cCNu_JCv~w)shn9u5my|NniJJuIGV7*7&H*i%S(|($WBJiR3Mvm4I7#n@d#JXCFykz45xpnR6J+>2yT3{a4x-KOZ4\?4WDN7+ZU@roIFZ216)}u%E_M=cSh&j^A$y<Yl1FHz\?ffJwGpzE|58xRec-=nb>DXOHiZCflnSr!=NCGp7wk`r1gPB4t\?x)b{^d;3slFg5-mH3uayvJoMM<D}E~d`BMrlLJz4Y<VW8R+s2nI3ib@CEr&>npL+R8)R2}s>}|aj)vciUcfxsEpO!}1bMDIWpsW$hu+*Z@zW~RlG0uO<1LLC6=-1R6=`wjE`m!|q`n6LCxCKPAaB}e^ib!x<u2)ZzuXb&_DzOzd##;NLPen0;Losp*ufnaE|IBl%tyM}fHC=`\?DTr-Yo<wJ$K#dmu1>T$$MJxad5wfDM+)xKwGe(+8)jrqec^lbx}PeSn@kIW$a}|K<iV3dj%CXDR6UZU)^5cLcPd>>`paa2^F){6^A(KHy@B4Kb-CR)$mm7t!L54Xm&Q=;&R*3J<>DephaO7|sh7t)<mU4jT*ok%W\?2`kxUA#@n0(5wUPspxdVa2L+h!1N0U=ZkgCxUaIiysA;9QpUJn+wt+ob&v2WuYR1ust^(iS-G_X8%@ifa@DXKq0JklVU9n1_$F&7+BUsG>iV)iGJXxX|Wr^%-5EcWm3YPQCK!fb&CB4IaBb6~2#jPVZW3j|Aiah\?-=6_}4s{|4vbSQ$gbVY(COqUu9TLt5=#&Bdp!0;2%3wrCuU$o+$98YIPy1y{P3&JEDrn$#^hKK7@1-lN<*fAwnm1IUm_+*nKitR>XK^^V=zNpHzF2zt\?ZP{#U9oxqNb$@b25fl;!YC_r3plJ2Bo1axuJP_GW=57ETpzp-YVC+&H5NYBloB)g6RLKI+$r_31RiDv6bnw2Ckgj9@nLXBE}<s4}a~ZQ(5CP{<QL$a;9U37yK6jpc)14h@Uj`ckbzDsnNwZ1qvBPL|_{xF4hK1SuX%<t9@!oI31mSO4-t{PW)WEu@gn(4Y$NXfa#km$7TOBFGhu5~Qa%)Oeh<Dn0b4yNhD3^ThWwZXtkN4XdMSD=P#-\?c8iH2C35\?`F~`;TZSP8z{VS!p@dN^KFABzpO^5(Q>bnOlZo(wK>%{FT8iMOwT`Sg1ZP}qi%$3\?$&|WljDA!Q@j33O3bT1`m6&p1uaPjyl8uNKBt)H5d;6lR707Us)cUih(HHUO&=Po`zu2b*qlTk{r9W!rT5n8|K9=1(|0F&qeyY7R2tsQL>Xj$7nn$HTNdS8pta3U|n$B>sm!GnN`42@45nZ)~n%GMrx}3~6lNUt;+s=b_7WG;|4f\?ga@K*llkn$2}AC-xhTCk!1IrZxEi3LvO#Gv@R#ABM^X`BrIm_ZfvoJcQpzBDBkStF@e^jv`o!f{@q-v)#R5_5p>MeZk|Mbb#*mIuun91_l1!8!kmNX0IlmrMM1)v1O7P{NbYOA6m+2pM0J",
"{+VYdO)fX45VmgJ!>}8<@u;~^Z`=%mt!=8P%Sg`&sukudVFYFI%o4R@uqKEDvtJe=m(JIp*tsM\?YBlq3Hwx9DaNdk_gQ;~2a0EDiuL(2Pi4A1u_ulr_mn`F1Vy36v4WPafP!9ayBmeqY6uoXK{cU1s6(}\?49icZi#-fbCzR\?ABkT9pbYm@VzK18Jg{$1IL$bC0~g99G(6<RTHb8_bn#0HHXQ{)p}g5&kDRE&DXt!u~;_*SR`>eH~oi>VdA4l`d#IeXHNVA{R~1D&_DYUiZj(|(%HcoELZFgV%%k*4;V4%w`)K<62Z{siOdvgA_WdfsNXAwh!NDE_=yR^pT)l6Y=N;Nw}Za$iiI&SZTO_hj;-;E2PZpd$Rwgf>Q^-Psr@WzL7Rz7\?mu;hCs`C_fyDsBuA0M8@0\?PuZfwau4T)TZuw)dT$O*LM@TIuc&M<4eQ(SxB=#rf<E$={zf&9VbC&(LKM^Vu*b--1#WT8\?y_-E8{|BMMr&^-kw\?|{A0Mq1ZKZc~u3;7YZZgh%1%h\?@a{}GsNBm#RdVbGED3#6~Hw%-ynfZWd;1F-W+=KwW4kvL95GY%c42q<D@WO!Lrp}snAFJgv_uIIeY7I$>o8uCRQ!\?ALGVq0gxbn77SON%<9rCYH(s#l-IeVveH$$!(#rV;u9V(8B1_KA%CWmn0%x{tc;hIdKVY*w~p\?JsBpz_^RYlSs4Tbtl_M<Fl<fk>2P3FIspL}`zQlCR+cYJ}4PGqD%|GP-8`289v`vM=E+QgXOrx)_M#ZaRYF;tt@<sbQ))6wK9R7<au!VMVT)<O9b<Qcb-tRC%^bu)2J6atMKeKr46o*uey%8jT(|>*n8MZMA~L9Z(wGc8)oN_hRKd25SR^1D{hQ>9xDO5tGs+N(ub1@RRpbqai^DagA*VEU)h\?oe`I4QHD<P3BJ;cJ}qEML&5(*cpUQEnz;PA$UI;vPak0R{lLtPKQ<h1Zd|OQ)U-@`voziPqb+i}QyiU1>3Fzo=q4BDH{ai\?j-Y56f+)PWKTm#pUT^%b*~eAxHAhGz{L`~y&&Nx#-G5g!8asQR`msaY-#C!yErp<\?v%s)%{+Q&REgD0%4c<oTf_X;$)oWtmOqC7=kCiT_t-k#}JVmQ~-7ooU%SaLFEwWkOrVufPWJK*R4\?hIb+=SI4)qL`*_7}aB<dl\?q8`mvc+@aS)xcEZ~3alT`u6g!`yuOTp<@=b5!\?pK>jGLxrLy6O-f;ln+hw{~6=$BDFAYgY;M8F>rIxx5!%VZMiz&M*omjVJKS(~yj8-S&0s3bWf<y11YdBW2WlauMGM@UmMv$dgBtR($FJ@2%(QnH4Yi>fm`H`3dyE!\?E>S-ykr*y5IBk`sfsW6MPq%DMVk>#$$vVR5ao%uRs@`I1*}^z92JTI{3RZ&kL+Jvujn(DjGV=2^<_mKNtJ2_$)AC(jd`KflhpU5+#}%Q{T|t35TuUDBX<J;`f_yZgJ(jd|w7#uS|t93E9^gJSy_b*P0z\?yL+f=Ag>|(U%<7m\?e5\?yrqa1m`l!IxKvt)bH%c}tzoW^(ZQk2$p1YuCd&Tup-)K;>g6knP1LQiX*(22#h&Hc3<C(XT\?Hg5\?Ka~hE!\?on(71WZbNs$<)U()j+kv4(TL(G#Gk0uq-\?Fk;PO|7nHgH-|TjrQ-H~5BDs^GTAaM7IDZEQD9sceH=mY+AEHnbC#sGwuoJ&YNeQcz1;HdhRE<VnGCSXf\?$yJTcSxL=5&Q<K4}DdWBgr<(t<f66v+cK1X67Uj1;XFn;q8As6rqX(iQH<kfV$BL<CC&%o=Es}YLNd%OJlnKI7bA7J%)eS;+L+{!2Hu2\?pTe!~HbJ^0Qi9Q9lB;xNR-Rg_NoBpjLmGtQwU|fkr*I}RSYO8h+7`VK991wYQZ_S|=`_k}D!yuT{@%F%YVhjBxY*B!st9f7RjmXU$fSi-i0imb~EiI~uL~Y*10*o_Lpo#OX8M;F7!NIh^7E#j4I%Y_Y2B`^g2r;BTcf}2)Cfi2NlCyo#Q8$ZNR6nh$(hq$p7}4\?+5{fe3tiN&%HqY_-b1fbM6hgq^ff@w^TL5b>z_L0|sm;TC&iX)+>{s8Cyz$U7=fJ`6H37;Nt%*&87*=x91_{N!5Fa*(ztEzjd%H!ttFR<GiZ`!<B)NR46_fFP{`m!NK!<BHg|EZXu@C0D&32Bu`WubH5QIL@f\?Qe-L5>JO\?&yeQH0%qk_^|BQ=kWZI@eboy(6iN|N-ZvGEY+0U=yOzPf0_$(uY`T!>E}|H2EwQWK1I*~pdV4sP0LCqlZNt2S`P}#CF+fNgqpU;b^}#WU-SI*vGs^bnkk@@aaB&O)>uV==0_;CKac>`8%}zZx#}b`YkuSNIo)d^Y9&Xk_NgL-K=-&yHC#4e`7upz<nF-pfSim~fD|NJ#5isamfM6z0qVZX5gwN>Xk2VGjN(Kiar#m<5=sMd#J0o)ij52Uqf&s5O-~27%D9bN)nc76*(ZPPJ#fvym-H*uh3ELI!>RR#UMj\?4WF\?`6RajTuAL+f@Y^U`vOTjer7PFvvD)Gv<QHIZ=zho=Zn5Y*v{$D(1%lz7gx%0oj4}Q~AsIBWAZlVpYQ+o<hDvOa+6Q@!|(ZB^!*8Ve8aZa~}W4xpjv2FtBM#;B(t\?ol3eKme;RC@#s+9iYCPadvi5oMmHJW~MlqgYq@dJ7E#W2n>rS\?(iwazPj4lDnj+KOcHbek\?9+z&WYZ_Q!bHAk4A9!ETE|)~sjUIojTi$Zj)itB|&`=re=<d8Ts&DPJZU)Z&2fNr;L\?T%IICF0so+$KOkI2i~JMhR<VbJ0xk_G!G)eM2Ab|#pc3F+t!t)Sm$HQ)DGxA>703Y1U<o59KGc-O^B*yJhhH3T31`6mf9^rSOZDA4vz7GpL6nk1p5*e{>@A`\?-Pzq#oE8NV$oPKB\?W+7&*X}l6}O+^=|||~ZL=@^H6)$MPwFcrD=AEk@\?Uk{6xpLDB2}FM+rn47-2mV|@Oj#^4RH~+KmnD2#Bt)xFMtS+MW5g7Ww)TE;(LQa=UN{~yNp<2Y8sbLYTYxl__ch3v;;w_Kc`do3Xl#{4yg;MJVY}eZHMXMPhd=ATi_Y;;bSIzGbJC%GibAPdTe6GN&cU0C^8WR6C-==!8&=$pl=d%d%\?k(=ivs4uEpi{EQU-MNNwuIaC_H4(iG4GW7q$E66s$G8u6`O{4dlASh90`nP~svZsCD>-xzS&R6=pO(Dpi|FWzXJzn_&>9qz%kF~M6yk@3<corZV-Hr>~X_HL68lv!)3\?RY~;on+q^9<t5nF\?S<B!z4A9oG1oe$3!d{17IJ!N!QwCle>xA+rQvZ9|c8C*Bu^tWnxYj8R0RCh$zEAt3_K@zb89dkC>_\?VB3B#IK$aymc\?yWX6IQ9xOQ+xCVC%XCE%8HA~nxbgYRBEC~qA+7KLsY{+*)zg4X17k<2Qvs`v=KRUgTvq$W0JV=(uGfnM`+T=_V39F5tPxQX`kOUfsUxuJ(30>EJ5hcTq_YeK3>sjb|Vgp+K)eP\?@l^FbQ>pdo^dP8<}$o2s@D+f5%exir>eC-bHZLPU%)NvzE^pS=on\?^S*OgXFdd^a%23yR9lL+6HB^&Kzw3X};FLSgU+T<7ZtkWgIgn0rmZzV&qIm$JgO9bv6Ph4j51Vp5N~mbn>bz4q8<hdnJVOHa<@<2$8umvsPQ=)DDI6YEsG*N}xm(#%51bb=|@WTFq;{|0ffcWZ+S9NHjKdAoa1kei1=;nAi5fX7LnFFr>^gAEbJeMCM051#TnufoD`(87p#GsCE\?Sj*j1kvqsZ;2kTnuwur|}_{O***B}~8o7soDZl=gVdcJUlKaxo@uGGXCL{Z$D@uf2rdKCX`F9*2oe1j``+yuCk>Gs4FifE}`\?ykByX+vGbH<JXDW\?&+w@S5}IiShbnc`A0_\?J(sR)-5M~X(!5y7%FsyF9>BwH9BBs\?j*XCj_P^$+|>P7+DeevwydJox-^ie0yZz8()KZmaC}2Df;3)tTMV-k=>Oeg-5ny_8tqz%Y(i~qSWUmn@3Ll67lG+3S4Bp4wT+DnXt}V7eqyZmlLu^l>w<<#Z_nggCbe9e@$(T(0n\?D6a`5u5yY^3OSPvhUI7Zbs^cc7h0u;WswuMG$rp=-P4Ce{{vuE!*G>=7Q8YC=60nNK7up#R;ZPa_20wVu>",
"Gzr23ai^L8lt5fuk*m;NKJM)1B_bfS|L%#75Kt+(d*T#gvf3Z0{$g*Z{1+SaA3|x5+3`q>!h&bj85XD-W0x!Ya2O-V&!eznv{OSik0b5g*{;hX>bCCFIS}HpRt_bE&O$7jhX\?56JE{K^Z<NZC)Y4{}-(w=<dOMWV=\?R5{^G8v~oKJ5ZvjqZD@=Gu~zbBCCV)3fjhVW-_W5kn^)Ls|Z<YawBN@JGYaBcwl4SpED(7FHX3HRu64RK_-BAR}Nbk>qnImy%x>7Fg<aDX#@>!Fh4\?_XrT9K_YP(q+B0;OQE4J%@(X@EQEQ\?Ao_Rb#Qp-Op#_iIl~@oMSvjPg2qv0`<r`MBWnDXapHZm#Jn7WKffy;5E@0yjY(<m*IbjGAL~7A;;a6e;xT5u+#;so5XHH|g1^puhMSTgLzy8P%B2tSMHYfGM$>|-wx}{_$J~04Sjd`~<d7`\?zTbXfm0m4dSgHC{^v0FrdW&{kLOcl~Y>lTETAwVw67bj\?+9&&@oO~Vn\?T@&Keg0R2=cJ~\?n>x)Bnju#yGH3+2)DfKD`C5cgdVa>sSHI1jG%79p%PAAv{F2S)rmIYXIOw#K@V;brM6Yi!`PPbb`f3bi${4E$_*DRKULXeS{pWsrg*4L_*_6I&y&(rA8|!M>T_iwE=lv{O1eedh6^&o*Lnfml)I<HUaUSFmz<~AGm1Tsxwn@bjYD4XMW7RHqkF<SAH#<LjDfzA}Sb|qERgUX2T*z$5dqKZU#eHbj>v~;GDPvElxXkgfN_drrx_nTF{Vs=>gwn<szHMPgN=E_jOwPekgNd<Qbncxk5!lQC&sA+Fp-p77Q}YQW%|{nSm-(Y>!;dJ<O#{q1|MVoVpjJEDIz$ttU=LlP{)Dj`^qpZ~Wv#g=O3<\?R^9)JeEP\?@bwyuV67F#E0q(x>\?f!<J$))eROM&=NNIIqk0\?fw(ryqWg`F^2I81YYKZa@{LD#kZdx>$2Ajb#-#M4@FbB\?p-Fz`nfXDKVWx)=RP48N0lP}YC;H!SW7&G>z!7CKR=!RE9|$Ev@o!4pwB7CcrCfLY9qkPs!6Zu`1yzl8O8HI^Sh6VdA%H_TgUgeOp|2f)Jx`PtQRX6^NXkwBpVR(d3%ufF-JN==RCprJPMJ^H^$Wk5N=Ty)YIVwp`N)-TZ97D\?LdD70w-mw3QL6gB(-OFL%SH}p<5!*4f@u{gSbN}4t0B>cX$M~LWoxOTB`=9\?fejah-ZG=U;Do!T!VSbqEo;n<EB|T@h5)ZJO9$`r&m\?&6))DH_<(bTH;#t)`CT#U&w-qjk#Ru>aj7A<veg40u9jmlQOCz+V1&#Zr<eLNHJL6vqFo*-aq-L;p#kg1rHt)xJSv1d&RG%R7TBD8HIWrx_cXu#aD}TwOQO<<ivZ3h;9\?d`>U<SQXh\?$_Bx_0+e1|RzPppP;e<(3&V$\?@P5e#&<nW|3nFDoNuDD0P_ORkX}YT!`tu)4>qBFX~0Jl9&I-8G@#I+#R6nQ0J3ZAB8J$h)bdOw4E\?KbQK9wl\?N4zT8Kob<UFtl*DJ`J(7)jQsc@P_Mh!s1)ByOSK2S95Rtd8zNYD9Zq@4*BVsYiU0lH;JrhrRm^4G@E7dxunpXUj08BWr)S$P(tNc6zEmur8i9*yj$Taqv;J!k9BqzYH85spuga^\?D0o{_FuS2q)Nm#A~$+(4M7vakR6-Sww5aUb#`nU4R]",
};

#if defined(__linux__) && (defined(BOJ) || defined(BASM_CI))
int main() {}
#ifdef __cplusplus
extern "C"
#endif
int __libc_start_main(
    void *func_ptr,
    int argc,
    char* argv[],
    void (*init_func)(void),
    void (*fini_func)(void),
    void (*rtld_fini_func)(void),
    void *stack_end) {
#else
int main(int argc, char *argv[]) {
#endif
    PLATFORM_DATA pd;
    if (sizeof(size_t) != 8) {
        // Cannot run amd64 binaries on non-64bit environment
        return 1;
    }
    pd.env_flags            = 0; // necessary since pd is on stack
#if defined(_WIN32)
    pd.env_id               = ENV_ID_WINDOWS;
#elif defined(__linux__)
    pd.env_id               = ENV_ID_LINUX;
    // Linux's stack growth works differently than Windows.
    // Hence, we disable the __chkstk mechanism on Linux.
    pd.env_flags            |= ENV_FLAGS_LINUX_STYLE_CHKSTK;
#else
    pd.env_id               = ENV_ID_UNKNOWN;
#endif
#if defined(_WIN32)
    pd.win_kernel32         = (uint64_t) GetModuleHandleW(L"kernel32");
    pd.win_GetProcAddress   = (uint64_t) GetProcAddress;
#endif
    pd.ptr_alloc_rwx        = (void *) svc_alloc_rwx;
#if !defined(_WIN32) && !defined(__linux__)
    pd.ptr_alloc            = (void *) svc_alloc;
    pd.ptr_alloc_zeroed     = (void *) svc_alloc_zeroed;
    pd.ptr_dealloc          = (void *) svc_free;
    pd.ptr_realloc          = (void *) svc_realloc;
    pd.ptr_read_stdio       = (void *) svc_read_stdio;
    pd.ptr_write_stdio      = (void *) svc_write_stdio;
#endif

    stub_ptr stub = get_stub();
#if defined(__linux__)
    uint8_t stubbuf[68 + 580] = "QMd~L002n8@6D@;XGJ3cz5oya01pLO>naZmS5~+Q0000n|450>x(5IN07=KfA^-pYO)<bp|Hw@-$qxlyU&9Xz]";
    b85tobin(stubbuf, (char const *)stubbuf);
    /* prepend thunk and relocate stub onto stack */
    for (size_t i = 0; i < 580; i++) stubbuf[68 + i] = (uint8_t)stub_raw[i];
    size_t base = ((size_t)stub_raw) & 0xFFFFFFFFFFFFF000ULL; // page-aligned pointer to munmap in thunk
    size_t len = (((size_t)stub_raw) + sizeof(stub_raw)) - base;
    len = ((len + 0xFFF) >> 12) << 12;
    *(uint64_t *)(stubbuf + 0x08) = (uint64_t) base;
    *(uint32_t *)(stubbuf + 0x11) = (uint32_t) len;
    base = ((size_t)stubbuf) & 0xFFFFFFFFFFFFF000ULL;
    len = (((size_t)stubbuf) + 68 + 580) - base;
    len = ((len + 0xFFF) >> 12) << 12;
    syscall(10, base, len, 0x7); // mprotect: make the stub on stack executable
    pd.ptr_alloc_rwx = (void *) (stubbuf + 0x1c); // thunk implements its own svc_alloc_rwx
    stub = (stub_ptr) stubbuf;
#endif
    b85tobin(payload, (char const *)payload);
    return stub(&pd, payload);
}
// LOADER END
