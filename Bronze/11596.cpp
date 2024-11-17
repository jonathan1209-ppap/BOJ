// Generated with https://github.com/boj-rs/basm-rs
// Learn rust (https://doc.rust-lang.org/book/) and get high performance out of the box!

// SOLUTION BEGIN
/*
use alloc::vec::Vec;
use basm::platform::is_local_env;
use basm::platform::io::{Reader, ReaderTrait, Writer, Print};
use basm_macro::basm_export;

pub fn main() {
    if is_local_env() {
        let mut reader: Reader = Default::default();
        let mut writer: Writer = Default::default();
        let n = reader.usize();
        let mut a = Vec::new();
        for _ in 0..n {a.push(reader.i32()); }
        let ans = sum(&mut a);
        writer.println(ans);
    }
}
#[basm_export]
fn sum(a: &mut Vec::<i32>) -> i64 {
    a.iter().map(|&x| x as i64).sum()
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

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#if defined(__cplusplus)
#include <vector>
#include <string>
#include <utility>
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
"00008iBA9k^tNsQ&<PSAbBhrH<N`Q+AAb(NHzc#H&plW;HUg8y_t4$-2nS~!nWv34m*Ke66@F6f&-u3!sAiohg|Tsi{fd)F>FXszaRm*\?qWguw9\?+X4Xf<;+Yg{<#ONNea8NVcY6\?E_#SH!p-w%QBfM1a^dMY^Og5#$vblp1~V2jQ9WjC`Gg#mDCroH{5L(jz<IJTiRWeocA;jK)O@n&jwC(bDFI$tLxLB#q>z2BshUy<{mD%;ovqNYT~Q{-vL-S-%40chN(>T0\?e3_=|JC>TKSclaZ)1ad{W(jMTK`$J6q#dv<66irI^GP%&lU&+l&q(=&kc7A)9C&%\?Iwh}|Z&P_$v4Se|\?AEye;rLpjowwD(J#^7B%RR!3y^a2Gl16|UA3=UurV;o%CT7kOUs>fmn-VXAWn5{1iTBhxaZTL%3D0D)$*S4=U<PO>0)x9~\?D+aTA5;jL>oVECp8rjsjY)j}tipwj(Tdj5&Q!BL1F8YYxS1D^Rq@{_Ud*nvD*<pP+-4$S\?i83&J3&N}qLCpX{2(DFgWEB$cw2N{AxMC)d+%TGHi5ACGg1+T^hHCsYs1gGc3ayTg<qs;A|4t0=V_U=cMxFJO%spk;E=4(#4vA{UcRlXwPoG0kRP^at(`B0Ft\?OYN|%U1`D#\?zGurLeSF2<|nM5n>bKUE{LhYg;xVZq!LQ__o4Bn(mOsOh@086rJND7tc0+xuIKbI-2}<+<X`o\?m|9iOT5wU_SG#W;DQS%mdS|D_{y5o9_a8<2F`;H5LMpoea#W<jIvpUaX2{M_4<&}At(;&6JFfkFdc$I#Ri`vjT$$WtuG_$8yj`EI=Rl|cc`-2c8m8zT=kjkhPQWNxkB!zMKhH&KLHbue8tF|C7JCy9p54N!Q);C-h7*Y!5^tmLVwn-U3qGazd~=#lhIeJ#xpwN$kKt!*@44~pvbrck;9cjMM`fi9aB~|Da;R*iD}3}e=Ttzgpb5*$4CRkxsuGL{V6UnV5`QKqVcEq4lHmQYaHeMcSHEnma)f!0hSH;L*|4R0<<<RME*TM8FN!1GX_}lQm_Flq;da1F6KVA&UL{lGlCqzN7Qtl*$dCiPE_A|I*sGHP(C;FM>0mZDK0FMf5lhT+`QDWrP`|*>b^wt+CZ8GD1e~wQ-TLKD4J=7-~_^lG*_Wwx0_f24{W!&!b&ks1`TWU``1kxo6fBR4PopP<HfX~W}vf)QsGbbaVQ\?$1smqZQvv(Rq=3mw7!P+>uX3AJadY9z+CPE#m(>Zp;-pkT0%kiZ34%98`A<Mpv9StIzYj+My@wFkCk)K|dlLA<(9\?fKwU~-#+liPe&{cAO%G}t_<q0fkYL-v1Ea|(}vE)<C!b4#;zjoL;c7zdf-Iv;AF|bp|_h4H}qN$KrtSvEA2hW>v^wqQLT##YdA6Fmh_VVWAh=+V0;&ai~H`0Kf7RU%{@cBnM^eSyL<mi$30o`e6Baz6fBUgU7)1e6vRpXOck17\?TXeuYavLR+5mh|9u>=&=%NWE}Zl2k3PZVs*LnHQMs^fT#BaD0\?K8UA}R\?umpZipd*{&sgN}77W4mih~tfhWESRd&fN\?ej}1(4wP@e@>`c__aXt_ky{~blY4YfP+>BDL|zHX8)R-3La051`XXLH){lMbtYg`7;wK+iL2=P%CjX-mh`Q>rWrS53k&5<HaZ%kE&4}H95u(Y9marQEscL5mz^sLaA{cX!wo^n9_CcH}YfV3O*<2A*Ty;=sD_*8DmZqP8S}f9OM8e}LPhvG\?(UOJ{t+sAFd`34ZO3$(my|65h<$rJWJq(cN<15E$+8Vl)=fXh|y-D%Jxv{u{V<@i&k@&_`DGk6lCO~f0a_!egRL\?!(^tPipKoj6ddEWc+qY|swE^ELQsB#=Wp\?PAV=C}8-0q1zLOjwJJzFa{B%s3*c=vxfC%Mcl|22SesxPa5<$\?0Xc;*7g@W}>SMtT71*tRyKmwy04dt1#Z`CYIEDWls0n#JuC3%O@k!_E2cec+iGmn+-TOdJ}@gD~G%f1>7v(8`MafU#mL3;+Oc_x^wwZfZ6rpwDwu}pI!jSgg(Sw=i+&YM$!Ij35fW<OE$`E9f{YEK}`N>VVL5@N;Q;gHL2aVSpU4hX<i~T>cNJ(5t+06&aE\?s0YY{-;T25uoTg~9yRk(#`yQTt@~}4>UYs+*+>-R-VsGFlFs#ots#!Omm~0kU$4#b5$2_F;#qD%f#x+~qDHE=+Uqe8qtepiOP#YC%mGGVfx@exq1~X!ac+3BeDn76$1z6JX|G3B<_hv`IO(rqprA%r_JZEmvmr2(`l5#{kB!NQk4wa1WCj3cvDl7|EIc)h$=P8Z8KH@t>4;#6_-qxQIPZH7EqvU&qphDs_UF-r2<n_@Tq}Rs6l6\?^^;|u(RmjSK%N4jQN7\?9O^!PG1IPi56G8Hz!~vZi2^OY6Ss_nm>G)zQ\?nEh2yx!~4!{JOq1hzFRu<V)_<jY}dCBUxB_PQ%gB~P)Xg@j{+JkSktLH+M3&`Q%3t)`)kf4Q<14TRPz\?`M7LssyYDKv+GNQRw%>b9!l_Opc<JE@{;krf-O^vD)caI%wce7dQImi}bn$pR#{)!qu-t}G@a~eZ-UxST0UiH0\?8sE*$d%6I^f-5inpE1=%S7W+R7^dPH{9^zMLUd-40c^*`;YHv0`_s&(j=Ek2#qT\?3Jr>GN$8F`!h{~C(L-c!NUBUuu7-7TlF;(6{rbQtM}<0)a|G3PUdsS($|1N5-}`W0INaC&^Y<{S0$^9C2k8muRS!nI+IDY{LaY#G$yGr(7rb^=haQl&y!Fg_b<^X#8!>8>E_Ryc5fQUOvu(G$&5!ArH1(5Ptl92Rw(>F0gKo$b+r#=qFyAXhTA7(T21olguU#rtDOlfl0$Z71780w{JvVG}0Q$A+95IhETE)k<#iBg!*-UL%L4+IVlQh{Vf6oRuqAK6aOkDouW5s=@<hC(VU^zQ758|(_JvkO9>EMLaNRYdfYa75CwIjQN<eEKK5h\?d5u~rXbGMxp6tv8Rg\?7{6TjM}&;KxH=7m1WrZ2e;eyjm~lheLTK{_hK{6`pYy$8+<Ac;)SB=l%Kyjt#-P*{4Q3j\?%LoOO!OuY2M|PrOET$1S;%c^F233OJIo!nq82|umj5BqnT4U_JT~NFm0x;H5)E93deCa{{fiAj-\?2SWaX%7MgrfV7LyL*n>2_)H2R8DGc2W6hsTQwswjlU1Ltmts&&E{3hc8qvM~G;tza)!bwltlk0tvJ0wEGu{fybl<Xad_kAtXAj2buZlwscEMExjKbX0*gFOaN3bv}(!opq+rpX8GK3{&1SGY\?NO0xM\?ISA8BI2Zm+xw`dl&+Xn}B7xh9X~o=vf;{O^R*@dqyj{QrGT$9fzogwzKgI>3i5u5W9<NI2g3`liuVq&VWwteSLHDF0w(oHTI$bq<x5jm9oFNbRwx1)f1^^gH=W8ZWwn%pXk3p\?!m_ZJ{|m5s\?csGCFkf`gGKi%Dc9r68bIA5xz{7\?~1eOqmNL8wrAo0Dce79AklhQUQ-m6;\?ke@+@uQB0{%i$jg!<!I_`o9VsT!`WMg6;;hpr74ffY&D@+J`a)PD<nq&LnhU0*5Fvzx-6l8\?YY+AhG$c&+;FYh%C_aNmC5A}Igia^fD!TUCVD-S3(P)_*|9D^nger<2pgKEX{5Gk5*Ih)$V%0P~qSi2WhHz^3BvmaGiI1U+$L`txaIIu+Ttk`eZ;LD%q#yR0BjfC|GNnm8@XDK25c9GKyy)Queh8Gsdz!01Ye%O<EE*fqeB5%%A^4S&WaH3{CH_66F8PGJrkjR%U2\?$Dto<#;dcGgsM+yQiU>^XONY{JSXW9Vh*M8;tR9eRua2qsZdCnDvD66DM15O)V8eucY}qmxh6e}U;O++A9@T}X`\?nlqZ_pRRV_!o@kMomCI8lbq5YQP_}y`F>=Ws_\?HuliJY!9L2CTKF%9a*0^c8)Ajv3xY-(>Bk9&RAeH)^`1>ot-j`y%8_{&}#%&J(U$-${eX8S!+X^ddEo+QbI_=C|%FES|FMjUnoetu5tOKgR-uPsM3@{w>{{_!MoQB8dz!q_uZMrYJ;V@qY%%Y6UJxHGmi8rwYJ)9#AuLpn0`dB_);qe)deoYFN{0Rh9Li*n`0-JbrCvw;Z^bpYRxzg)uzk~Nxi^ynRx=Z@QH0zk5",
"lLT^p#%WILaK@_C;H#>~pHMJ=d8kB-&^h}g$G0MQjq7nY4p^ZeOO#L!<4}09A!s+iUJh!uNdSNz$0E|^{bHlrSOQ&d_ixbgjhexZ93Yawcflh=<b}|RD^CfKtvgba48zA4\?LxgzcRBjRGi1cuUyy7BJHRnm;N2KIWR%rt8HmIwb_Q_0g#lr~&Ff<k!_w*\?()f>r#HWT8XAb>0VqJTYH7LvD(1|Vayjg!Wro#rMCR)Hhf4LQ-d7|Hx@gAAfF7t3mp3QPwYq\?ceSFN)Xh==H_=~!%c+@O7;TnO(iOor`mX^r#(PCKrLqtH!@4r4N!W0gYXw|Ww&g8^S=&VZRZJ#ydOe91gt@Ka-Xc\?zdDXPwvLndWzynU!@b-H>PA^Xf`%vABiQBrT8PpcLP}J*Zn^ItdBwe03#6(dndv9i%qtnYrJ;!ge{>s!g7-up~BSLn7ucBMmM@6Vzkbd@ZViw>F`UB@lQ`fs79nBSstK_V3iuAXA&I!rofTQ=XyXAinZl43%_aeHyJwM~8\?1m0{c9=s84xtHSSiX&Nii_$h-*0W3_1jBj&|-Y)72E^An3\?1wILF_hjJR%8OY5P0n$wde<8yhP;L^>fxp_Aqy4;F8g(QN@^9CS1<2ktI-Kta*lmgE7{1{1U(9L+~\?B%iVcA<prXB2v-6LOAhT=T|uuBm;K+;G8RldIJ-@*8+8~^f#R_>DkZHzKN3!q-o\?NK7ZKzCwM}K00igOO\?7Jv|2ZDrVRv38XPNtAYMZ;4<UOCi\?7UOf1Z#u<N#3RMpvyPeD1BwEvd<Mo)Cy3MFFZKs@H=M9BvWhy6PSwsz6ZV`8kgK+41MyRJ#f-lSFC\?@nWR}6d_WaHz;4\?bPd~}2v(8URtp#P|~TQ~%&zf23Uz$6@\?3\?KWhHxiQgL*sg!j1yqGJHwDZujqlh<SZi)q9V%`&%u*AY;+TbyZ<=KH5i(`\?oA4N^<H7T+fbBxT0fwk)4!F`kG`O)L3Go3@m\?m@ag%n#6t02_wv9c-R%HEJBRz~auv1SuiD8=<54G\?(fG|OJPB<9j)TmhCk|\?)2I<N6v^W{E{<%yx+km()Y-URBl5^^2xL$M8QWXViatP`%3FS<d@UuKixnVZG_1Hs1Z^~3vM_~OyhSGr-FxmXOvn83za\?Al>yDen0XI~#8%rD4L\?ct$eX0U_7R`$w0aSUa5auMuJV-RntK\?Xz2pHgrQNsbb2QCTsjPMBL8@<34A^$OJb7K)!8!)unU*xv};\?Z*!ETb46HC\?GU36nY{eHtK~s96rjCP^QI_og_Qa-c$15tbPfAojfRK(XUmpn{V-W_hHyy_pn7lkjhe<hhhB)ZEPUv13Y>>wp@2y^>!cv`Gn!U)S2msLJ+GS^aKFJA2@J1#f\?qJ&aA+y16q|9n-I#sd$TO~idyf_}D(\?&zO9I}tc5JJJrWxB3s(gNW09BF7W^\?$wEw=$Xwpcza=)m0zp7vB_K_PRmsDhdhy\?)nB2gq&dVz-FSRApdi=82^)z#<jwV*_0Sq<A#!r9Ucm#Nr(hDuH@l`b=%9I8UPRWwKK+wR8aw1H;*8%Uie3{9{xU3(`rZ(k0NbS7Nzdxf<!a`YJvxXdOF&amcfCsm2UcaUVsRsVX3!+zNjT_qFfgG=J86SR_VBGFU}Z>11\?ocj~$h|F)hujLFa7eCyi^&O*e^`{A+}$X!9-uuK#<72O6M2x;^gh>PUct5y-1S-S4)=8KOT(_O!Q-Ma<k^@g+;S*_B2VCc5t)gE%QzX=I=Kojn*vp;p*I;MX1Fg8&qFVD5Ev>wb9=;ApeJ(5R`B;3Llp_$P9u`LErOkdEwqO=Hr1Xb9&>zf<9;RVxfpU6UwEz1em!hd33{!QsKYE(!k(S)uxbT4}Uv+DEWpGcp3K8WJw9\?hKd{kI7P7)p~AdD@2+XTbfBHFD;qk#_(KbvA&iaS<%(-<_\?k0`|3JsxneZ(YZfXunFVp#ZtHg6&T=2dp^W*zKMW|I*2Ol\?ZVfM#&d4aqHv@iqab23ho(_zoWopx>{C4-=}D~>{pf@;c^SyUw_uEd_HvD3wsNle$>7}q&FDF}+@0ksSm;vtbh2*zEQC*52r~V>2K6MwR;uvsYBSlLzySritpHmB27cwXm23F@hw0F6G+;7NPH9CEo3Cc9Gp8!1p^~Oyh@M)L`H5gmZ5ZvK;oNBrYG*fy{%JnFuN&*Kpm}6h^KvjK(MRl=xl!ICQBV8T>&+((z0P4bkmi-cP>5pK*wW5O+i=I;_)_J>-ulz3Iq1O`ybJpF*okv0x`X_m+LnNZp$G2HuNb%%cI{DOXE0w~xT^u0riGpF-3&<yj%JtT-h5mphm{GeGt\?{>HlKT|\?I+;r40)!j_l_!mxeb2$yelHk|CL4XY5stfgkh8uyq)~$0m#}iuu-N|o`AE>A8Joy%>L{)WK=7EH`sPFN&U*#==Xt8y;$dT#6L}Kv01a8h}2q*9flVmsdW}epKxgTy1)v#W0dpj`=gF*T\?v}m>XH1jDEdkDe7Ea_n!U$e5kx|gHzV)mox!44@K6_~Ry*Ivx_%=!$FzzW9x+U=9go@EC{-#aJi~afZ=>VaZ5-_<XL%-\?4B`pvq@D_7;ZG-%hs-y&JTC7M-uYy|FGMx5U)3LyQ-hULFy!3Y&%h8D9mc@e(xUiSJ6XP5\?NhTeovbOxj2b~4VOi*9YgjU}6`!UHkHd;Z0s\?Ff1MoD)q_PT-+kl3\?gYN\?z5&>`+o-za~3@{N^o}9WqlzawSf%k#gn8a+yjWg4Qkn^&58`&X>L&F-6!h;>js4D@B6b9RHW7o#Q5F}5S@=fTyPX9#UFP}{u^cm^g;gF1IiX_%\?cB4o|Tx-1aX8$mMKoz}cl#kcAb4Frz*I|%H4VqAhDdUT}cRz#F{;!tqY#g2p*rvBnJU0E|aX#ayayQfLAMIrMo~Bf1hQ|l!mjD)US*ZmN!`nn}v_WVr#4iDgWBR&^BeJV<GGy*p7G}QdO32A1<~gQvA4InnLh*GJ5<+2VENwI;qyn897eyXms|E{5RdRq}_8~i)zT&ZJ!t-<%xUlb>3pDmXjFhXd7q|b2h%p*^L9p1^>z;_uh;MM7ty;WiunMG2sZ;gj5M1r+w<\?AIRLKh+1M|LLZa~}v3*\?fH9sS2ZI_>~!Q2Siqn}\?clgAQ!rF8n(LG9`6v49$we+kyq*Hd@3a)FyL@\?*5v9{@(gpzAdJm8+~)nVT!;uNub>JKNIj)^|*wyyH(oCjasIgZlc\?wzv6$83PZA#CL~BLihv}064(%tOdfuxeJ6q&4(TPA8*m4e\?}2&=<U=))pO`+mILm*#q%pNpy0>TV@P_O1LJ2D4zajM0SS-F2uk4A6k`kJ1gmv7VZ{clTa6aC\?%iK1Vp}KlW3xdDBNqY4P$F\?<zZ1dDMuJiqUP74UPwbd-NFF*C)!VA|PE+IUIM6_+M$P+j1!AK#`!~}#|)u=ur^rlC%4cEU<KTdH-vX)D`>rm%=0*a9ijWl;Or4RI^>ka5DCW-$(tTe1%wriUeRykD>jveOn#\?3-wuD+At@MP%ekuYvObwcK)h{*dWugJnxYiK6p@FBkHy%sMREZyi>\?7Eo7Nn|5;Sf36_dMmvVZaXAI5`pAD>h7{VxydNAfp^KUXSr0Ef17-^V5mxMO^>\?QK(O;\?To~1fBlJ&KrxjK9Tt_6#WCpc%ll#!#`=IYCY+Q)iHk#X`7>G%rBs0b09sJ)|Xg-K(*A|=8EOHyVA}d)OIm_*=EHOW76=`J3p}ou*\?12{Pen3sT$+tAC1#mjq<>7~chu&<qAir>4A%U!fYv3a%Hg}Bp^`3bv%I7)rlQf<gEYeqnoGUVnGTnOoNE%(o77mT%#U0)^WP8EvH>aqtJjwQ)W<rZt+JC*;k~p`ZvtzrmT9+ByI*zq!f5aT>6Wnsr#oK4NuoBDxHW&#mRtS1o*oxYb0QS*3c-|kgJ{=Y5IP6JtZ0<X5v{diP)tC81h1*EE{|_|dNQTFKaor>+wnD2Zrh8P(!8!iazm~$ibW)fRSu\?M%9tmCvI}$YLnZyBa9(gt}1bi426!+gx76vw;xft>3`bCQ3@U+O(n-m!C2S4c@@Mjby4#yX^VPgbapNmU~7yOs-kCl>>{}WFOw*UA}2h1IZnl{MzJ#H9c$5<YlMTl5g;^iRSslHdS8qkd>d7>DVzdzkikQQgC",
"5V+G=g!_to;x%i~CIhN;v_WZtH|ln)&LM1NeHUWo6BXnkf^6L-OD19dx$Zwy7DvqDcwX{^dt<Ubm)}R0-HkNF&`R}yr}bmVZoiI_>UY6E2Vl9;C+98}Uk<G$_Q>C}hA(IJJ`mrR{2nW~8|u\?e#d!s~B*`7S5_UEq9L@J8I^6\?>znOSjKM*rCClZy5TPRH`>Baaiz5Zo$a}lH`sHi3AHmdDkr(-\?e<C%FeCF;1%#vw)upB)=o4jSv-(`oCWfvjTzln)7F4w!-+Tys72GmVqviMWpW<D8U(_>!0&`B%COt44AB&m\?g~<l|<DE7p~lsJUx3{Y%WP$|m)u6g6N~YC*2iEbA98s0GltUaUk_N02Ju$$&Sbygcyc#9+2hs%{j_#m;wv>;pHTxrA!&P10aN$_1Ept`g}kO`NbzmXQE7wCA%g;E$`S^#|=Y0~cj**Ilju8Qi1-N!pechl{QHZ\?m;&`Ed=E)VUgTD%R0)eGCHVmS\?XjzhkgeY5y=TpA>m{`U<Q\?IIrvkHnD;Nd<Iu^aZ$g<j)PCuST6qV`ylp80=~CpnwR6f#c1|kBo<$QI5spREkW;PP~=mj=L)ZM^VdEzj\?\?x)bCEgCbspEc@f^f_<;bBQM>eFu;<rsTvib0Xp92reUB4;&qht!a&Gid&yqR7=9Hx7XSP!vpiyACfF9o*j&ZpBRFmbsN4%*J-)Nv$22H\?BVZ9!Ww_+g\?HQ2pXd#^Yu8hKxGpb$`qPSa`\?8<1t_BUn^49I47sEopK*w2c\?3mLRN^BR^`)+TZ!WQegrNxbZg3>u@*!Fk~WBKj\?c#MT({<lLeF)|;@#LmHvo#-UMt\?m#;>2w;Kn50pMXfG9E^-e5~P`(Pk@(oc)KQrcSYY6Z`fDM\?x!HkE\?sKI^M\?<PZO$5DuoX*STu^G^C;vS6ZfR2PovywixHce|PMey<2UH)mX_1HBLb0PaG`ns5jsO1#KgIw6]",
};

static int g_loaded = 0;
static PLATFORM_DATA g_pd;

void basm_on_loaded();
size_t basm_load_module() {
    if (!g_loaded) {
        g_pd.env_flags            = ENV_FLAGS_NO_EXIT;
#if defined(_WIN32)
        g_pd.env_id               = ENV_ID_WINDOWS;
#elif defined(__linux__)
        g_pd.env_id               = ENV_ID_LINUX;
        // Linux's stack growth works differently than Windows.
        // Hence, we disable the __chkstk mechanism on Linux.
        g_pd.env_flags            |= ENV_FLAGS_LINUX_STYLE_CHKSTK;
#else
        g_pd.env_id               = ENV_ID_UNKNOWN;
#endif
#if defined(_WIN32)
        g_pd.win_kernel32         = (uint64_t) GetModuleHandleW(L"kernel32");
        g_pd.win_GetProcAddress   = (uint64_t) GetProcAddress;
#endif
        g_pd.ptr_alloc_rwx        = (void *) svc_alloc_rwx;
#if !defined(_WIN32) && !defined(__linux__)
        g_pd.ptr_alloc            = (void *) svc_alloc;
        g_pd.ptr_alloc_zeroed     = (void *) svc_alloc_zeroed;
        g_pd.ptr_dealloc          = (void *) svc_free;
        g_pd.ptr_realloc          = (void *) svc_realloc;
        g_pd.ptr_read_stdio       = (void *) svc_read_stdio;
        g_pd.ptr_write_stdio      = (void *) svc_write_stdio;
#endif
        stub_ptr stub = get_stub();
        b85tobin(payload, (char const *)payload);
        stub(&g_pd, payload);
        g_loaded = 1;
        basm_on_loaded();
    }
    return (size_t) g_pd.ptr_alloc_rwx;
}

#define BASM_LOADER_IMAGEBASE (basm_load_module())

// Ser
template <typename T> struct ser { using impl = void; };

template <typename T, typename Impl = typename ser<T>::impl>
void do_ser(std::vector<uint8_t>& buf, T val) {
    Impl(buf, val);
}

#define SER_RAW(ty) template<> struct ser<ty> { using impl = ser_impl_raw<ty>; }
#define SER_RAW_PTR(ty) template<> struct ser<ty> { using impl = ser_impl_raw_ptr<ty>; }
#define SER_INT(ty) SER_RAW(ty); SER_RAW_PTR(const ty *); SER_RAW_PTR(ty *)

template <typename T>
class ser_impl_raw {
    public:
        ser_impl_raw(std::vector<uint8_t>& buf, T val) {
            for (size_t i = 0; i < sizeof(T); i++) buf.emplace_back((uint8_t) (val >> ((sizeof(T) - i - 1) * 8)) & 0xFF);
        }
};

template <typename T>
class ser_impl_raw_ptr {
    public:
        ser_impl_raw_ptr(std::vector<uint8_t>& buf, T val) {
            for (size_t i = 0; i < sizeof(T); i++) buf.emplace_back((uint8_t) (((size_t)val) >> ((sizeof(T) - i - 1) * 8)) & 0xFF);
        }
};

class ser_impl_bool {
    public:
        ser_impl_bool(std::vector<uint8_t>& buf, bool val) {
            buf.emplace_back(val ? 1 : 0);
        }
};

template <typename T1, typename T2>
class ser_impl_pair {
    public:
        ser_impl_pair(std::vector<uint8_t>& buf, std::pair<T1, T2> val) {
            do_ser(buf, val.first);
            do_ser(buf, val.second);
        }
};

template <typename T>
class ser_impl_vec {
    public:
        ser_impl_vec(std::vector<uint8_t>& buf, std::vector<T> val) {
            do_ser(buf, val.size());
            for (auto e : val) do_ser(buf, e);
        }
};
template <> struct ser<bool> { using impl = ser_impl_bool; };

SER_INT(char);
SER_INT(unsigned char);
SER_INT(short int);
SER_INT(unsigned short int);
SER_INT(int);
SER_INT(unsigned int);
SER_INT(long int);
SER_INT(unsigned long int);
SER_INT(long long int);
SER_INT(unsigned long long int);
SER_RAW_PTR(const bool*);
SER_RAW_PTR(bool*);
template <typename T1, typename T2> struct ser<std::pair<T1, T2>> { using impl = ser_impl_pair<T1, T2>; };
template <typename T> struct ser<std::vector<T>> { using impl = ser_impl_vec<T>; };

void do_ser_end(std::vector<uint8_t>& buf) {
    size_t len = buf.size() - sizeof(size_t);
    for (size_t i = 0; i < sizeof(size_t); i++) buf[i] = (uint8_t) (len >> ((sizeof(size_t) - i - 1) * 8)) & 0xFF;
}

// De
template <typename T> struct de { using impl = void; };

template <typename T, typename Impl = typename de<T>::impl>
T do_de(size_t& ptr) {
    return Impl::impl_de(ptr);
}

#define DE_RAW(ty) template<> struct de<ty> { using impl = de_impl_raw<ty>; }
#define DE_RAW_PTR(ty) template<> struct de<ty> { using impl = de_impl_raw_ptr<ty>; }
#define DE_INT(ty) DE_RAW(ty); DE_RAW_PTR(const ty *); DE_RAW_PTR(ty *)

template <typename T>
class de_impl_raw {
    public:
        static T impl_de(size_t& ptr) {
            T val = 0;
            for (size_t i = 0; i < sizeof(T); i++) val = (val << 8) | (T) *((uint8_t *)(ptr++));
            return val;
        }
};

template <typename T>
class de_impl_raw_ptr {
    public:
        static T impl_de(size_t& ptr) {
            size_t val = 0;
            for (size_t i = 0; i < sizeof(T); i++) val = (val << 8) | (T) *((uint8_t *)(ptr++));
            return (T) val;
        }
};

class de_impl_bool {
    public:
        static bool impl_de(size_t& ptr) {
            uint8_t val = *((uint8_t *)(ptr++));
            return val != 0;
        }
};
template <> struct de<bool> { using impl = de_impl_bool; };

DE_INT(char);
DE_INT(unsigned char);
DE_INT(short int);
DE_INT(unsigned short int);
DE_INT(int);
DE_INT(unsigned int);
DE_INT(long int);
DE_INT(unsigned long int);
DE_INT(long long int);
DE_INT(unsigned long long int);
DE_RAW_PTR(const bool*);
DE_RAW_PTR(bool*);

template <typename T1, typename T2>
class de_impl_pair {
    public:
        static std::pair<T1, T2> impl_de(size_t& ptr) {
            T1 val1 = do_de<T1>(ptr);
            T2 val2 = do_de<T2>(ptr);
            return std::make_pair(val1, val2);
        }
};
template <typename T1, typename T2> struct de<std::pair<T1, T2>> { using impl = de_impl_pair<T1, T2>; };

template <typename T>
class de_impl_vec {
    public:
        static std::vector<T> impl_de(size_t& ptr) {
            size_t length = do_de<size_t>(ptr);
            std::vector<T> val;
            for (size_t i = 0; i < length; i++) val.push_back(do_de<T>(ptr));
            return val;
        }
};
template <typename T> struct de<std::vector<T>> { using impl = de_impl_vec<T>; };

class de_impl_string {
    public:
        static std::string impl_de(size_t& ptr) {
            size_t length = do_de<size_t>(ptr);
            std::string val;
            for (size_t i = 0; i < length; i++) val.push_back(do_de<char>(ptr));
            return val;
        }
};
template <> struct de<std::string> { using impl = de_impl_string; };

int64_t sum(std::vector<int32_t>& arg0) {
    static std::vector<uint8_t> s_buf;
    struct basm_free_impl {
        static void free() {
            s_buf.clear();
        }
    };
    do_ser<size_t>(s_buf, 0);
    do_ser<std::vector<int32_t>>(s_buf, arg0);
    do_ser<size_t>(s_buf, (size_t) basm_free_impl::free);
    do_ser_end(s_buf);
    size_t ptr_serialized = ((size_t (BASMCALL *)(size_t))(BASM_LOADER_IMAGEBASE + 6312))((size_t) s_buf.data());
    do_de<size_t>(ptr_serialized);
    int64_t out = do_de<int64_t>(ptr_serialized);
    ((void (BASMCALL *)()) do_de<size_t>(ptr_serialized))();
    return out;
}

void basm_on_loaded() {
}
