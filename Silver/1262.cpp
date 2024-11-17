// Generated with https://github.com/boj-rs/basm-rs
// Learn rust (https://doc.rust-lang.org/book/) and get high performance out of the box!

// SOLUTION BEGIN
/*
use alloc::vec;
use alloc::vec::Vec;
use basm::platform::io::{Print, Reader, ReaderTrait, Writer};
use core::cmp::{max, min};

pub fn main() {
    let mut reader: Reader = Default::default();
    let mut writer: Writer = Default::default();
    let n = reader.i128();
    let mut N = 1000000001;
    let mut res = 1;
    for i in 0..n {
        let x = reader.i128();
        let a = reader.i128();
        let b = reader.i128();
        if x > N {
            res += 1;
        }
        N = x + a * b;
    }
    writer.i128(res);
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
char payload[][2212] = {
"0000801yBG^tNsQ&<PSAbVqUxV=2Zdh091%czKq(<9~y7`%(L2AdY#%flf_azoOma#6<8l&&+PHCZhUnv~JHRL#9EYExq;+`ovR_v1uMl8X|l=$ou6eiO)T55Hg*b34i;VIERg%ygL{5zGBfpa9ShbaaFd47qTD*mbP6}H9Qwxk`MT$w)`b98%tK7t>iAnZKP;-\?0uE$ZvQ=G4H2HUU@ik9It1s+aOn9A!OS8>g7)`XzRsPmXbIA0{~E^q)\?vgR4J@%noAPJ%Yc&dh5P3_u5t1g%=CfAF<AR5Y+PIbwXdXrI19i#57k;Mt$LB&8UYlLq&!YwmOr*K~Qu5DNPIc*+9ds#(a9P&&15^JzXz-5Bxg$HaxsenNu&(V>PttNpEfhja0C^6nT9)>\?^%D^A8Ox*VaHD<W*!_X2%Sk55-pF@BX5-e3TyJkgWJE&@(6bq`rPd<CzV(!inr9S5w$GmkRETuk0Yd7mSZ^$W*#i9djS&m}Mm;PtKvId00$6(-nW^>`LOFho&W6jc\?}|)~l6^G!E*z~-F~K>E)u|zWiGJ#VFtJUA9^|(ew)~%1gQ+ma6d@$nSyNXh_IazGay_RPA(4(%8P3B}-#t-z0H5HW{^cz{I3ikEm&wMzzDs%KS_dYD|8m$LC2}-et#mYC!Ab83\?q55=+Y$XZZ0zs$8R3yy3%kdaN`aWCEYYR!$r@V2gS!wT(mf$8a}Dl7;_!D6vm@&3A>c8xkK;kU>;VO}NuYhO7oScdLV;G4XhZ(H^FKbD=c35%_WfpMnP32&QR|0aejDI=C^|jIur}M{6h&WNh(g!E2+`hfG3WkbOzQ4i\?Q@V@9q&D;AV<qHDoul))L643Af3LcuWdK}xtPXFCoC)bnND@OJRIl\?^|b{nm3haC=C6e6f\?D!EDn1vA&E@Zr4P^Zy{is@pa!AQ=KBcZW@>8^V=Ng$LQF4a6@*ww@!`fvWl>f^w+q5>GPn2Op2aPaSaDkvPCoqYp%\?N>Mh;_|`9}J5&*#PwdKqu`c`7aG0eBME{H&jsx6dA8\?PM*Y;H}153kTkg-6u6*Sh2xu8pS<h78_=NMEDnNkilw^KI12C#;pM>WW05&wI#0D3y~1d%QI8>{i>`OV^S1gT<$S)IqZAR=rJd)17*BW39LPwLnEKtny>C&l(\?&PDI++9B-=H+5`roO}<+Fyr9$aD5Q5o{O4J9<J>di\?H(2wyy*PoG@7)\?fbl@r42$B}mC`&!J}r>*6Ln\?OqNzXQXK*^nxTM^hx^nRjAzz-2K{W~l~*be#@$wm0eO6Oz7qyyrcSbBecOP@PaAelc<X@&}HUy~q\?-tZ6ozD$9qc>qK@{(3ro!u<`Hb`%\?AMuTt-8Aw4&\?xaA%gZdSo@nQ0_E36$mjjy(MPdFfmZ0(fUT4PYzB^}m-TY\?F{b**(+|OH=HS*er{7mzSd+6#^tXh}f4\?<NVw~9tVeyNW7dq78l}O\?K1h#_{`3t=P_gUkr+G!VgEQuwm9t^zELn<LED<G!^gnzr#*0`0eBvmKfZG4LKHuF8;8n(7&`5(<2>|na=B_LlnsgLA*S8t=EzWnw#txtzGEFgmAa`0\?}G6kFzLw8K_uX$8ALI\?%lBhZ0fEx5DKdi*j&}>y*P|Bz=ci+M9$xXxvKv*VX<__@tGvIZzpaq)yFKPjoDGok0nima\?W>uI94+}Znp=$V0fwY$-mc51d27CDU~niis4E%Wp~XAnT50YK#M\?kxYA)q\?3v<QeqH\?I)9J\?X7GJYKKp~-=8=yn_0SlMac{jjD~cQv!-(XtNGyfTC\?jh&k1H+62WF4u(9TU4i!oz&u!aYP48%CQ^mLggX%s_O-qyEXPu2V{K\?*\?kl>e^SLtB(->ge({m7-q\?s7s~(`<#(qi}^I|LFZ8t1Z<ZKZI!h4PdAl5bY#7s74sfHJ#cc>;b3)17$kxlKLdf;T3vSk#R4AJhBu8MYMK`F2MY+)5_U>_nyenLFHV*qt!9Gh!_TbXCKmvaz3;*~QtZrut#12yjueq2eMd(=9Wqib1MzJ=KMw<;+!Q82wneW=YmTip@&0)$dVehBxS+Rzy-N_c^~(>!qQrF&\?)49j_D6R~r3CVFINveJsj{~2+dX_@e!X$CP!{-pp~48FEFkQkhL>lF-&W{UPh<Ei04bborV4d)E*=g&)sZv!;US7*4)W>Myl\?ckTsPNBWowDBLB_|+#mvXX2kC%-&J<3u;JKa<|b33!tmp\?`j#a1cYAvFrb%>q}|\?]",
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
