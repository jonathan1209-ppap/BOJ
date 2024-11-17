// Generated with https://github.com/boj-rs/basm-rs
// Learn rust (https://doc.rust-lang.org/book/) and get high performance out of the box!

// SOLUTION BEGIN
/*
use alloc::format;
use alloc::string::String;
use alloc::{vec, vec::Vec};
use basm::platform::io::{Reader, ReaderTrait, Writer};
use compiler_builtins::int::i256;
use libm::sqrt;

fn abs(x: i128) -> i128 {
    if x < 0 { -x } else { x }
}

fn min_iter(vec: &Vec<u128>) -> Option<u128> {
    vec.iter().cloned().min()
}

fn max_iter(vec: &Vec<u128>) -> Option<u128> {
    vec.iter().cloned().max()
}

fn lower_bound<T: Ord>(arr: &[T], value: &T) -> usize {
    let mut left = 0;
    let mut right = arr.len();

    while left < right {
        let mid = (left + right) / 2;
        if &arr[mid] < value {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    left
}

fn upper_bound<T: Ord>(arr: &[T], value: &T) -> usize {
    let mut left = 0;
    let mut right = arr.len();

    while left < right {
        let mid = (left + right) / 2;
        if &arr[mid] <= value {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    left
}

fn floor(x: f64) -> f64 {
    if x >= 0.0 {
        x as i64 as f64
    } else {
        (x as i64 - 1) as f64
    }
}

fn nCr(n: u32, r: u32) -> u32 {
    if r > n {
        return 0;
    }
    factorial(n) / (factorial(r) * factorial(n - r))
}

fn factorial(n: u32) -> u32 {
    (1..=n).product()
}

fn max<T: PartialOrd>(a: T, b: T) -> T {
    if a > b { a } else { b }
}

fn min<T: PartialOrd>(a: T, b: T) -> T {
    if a > b { b } else { a }
}

fn swap<T: Copy>(a: &mut T, b: &mut T) {
    let temp = *a;
    *a = *b;
    *b = temp;
}

fn range(start: i32, end: i32) -> Vec<i32> {
    (start..end).collect()
}

fn comb(n: usize, k: usize) -> u64 {
    if k > n {
        return 0;
    }
    let mut numerator = 1;
    let mut denominator = 1;
    for i in 0..k {
        numerator *= (n - i) as u64;
        denominator *= (i + 1) as u64;
    }
    numerator / denominator
}

fn pow(base: i64, exp: i64, modulus: i64) -> i64 {
    let mut result = 1;
    let mut base = base % modulus;
    let mut exp = exp;

    while exp > 0 {
        if exp % 2 == 1 {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exp /= 2;
    }
    result
}

const M: i64 = 1_000_000_007;

fn mod_pow(mut base: i64, mut exp: i64, modulus: i64) -> i64 {
    let mut result = 1;
    base %= modulus;
    while exp > 0 {
        if exp % 2 == 1 {
            result = result * base % modulus;
        }
        exp >>= 1;
        base = base * base % modulus;
    }
    result
}

// starts




pub fn main() {
    let mut reader: Reader = Default::default();
    let mut writer: Writer = Default::default();

    let n = reader.i128();
    let mut l=Vec::new();
    for i in 0..n {
        let x = reader.i128();
        l.push(x);
    }
    if n==1 {
        writer.str("A");
        return;
    }

    let mut res=None;
    let mut multires=false;
    for a in -100000..=100000 {
        let b = l[1] - a * l[0];
        let mut valid = true;

        for i in 0..n - 1 {
            if a * l[i as usize] + b != l[i as usize + 1] {
                valid = false;
                break;
            }
        }
        if valid {
            let nx = l[n as usize - 1] * a + b;
            match res {
                None => res = Some(nx),
                Some(pre) => {
                    if pre != nx {
                        multires = true;
                        break;
                    }
                }
            }
        }
    }
    if multires {
        writer.str("A");
    } else if let Some(val)=res {
        writer.i128(val);
    } else {
        writer.str("B");
    }
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
"00008;7R}h^tNsQ&<PSAb2_B8`cj}LVV<#mnV@S!bl0%y@{~<Z0`ordiLOeB^$f~!+7;_~yDV&Ezs;OIU7>wa*5J>=Di99UXhG#ON\?F{gARn%P\?*t(F7o&xD)lqPck#>W0S5y;BcW\?mU^~l~TZxL4$LYZNcvP-l~gbiPv3~dYxoBiFzW5;|zIv7E)0@!t78VLw6;8kP$YO2(}vV|mD(z2P*%E6y*;Vvn7fTcnb(miG7ZoC7^99UI}f4`rKRy=WAzL$x9O5en#3$W(GUpVoPPM}2ei_$y*jlfx7bMUws)zz4FCYZY=b~<cg#)3_5J*&AIvQqfQV<8;#GB;vZXW!)Xwlb|AaRE^l0;pL2+NU9W4DKrbe{}(}5*McwO84vJ(#%@lA8hVnRe*v9klWW#hw^r~n>BTK2HjVS^#-+-4+nRw2%=U\?1JfUVnA}}0a0s{0^bYN%{S%vwJqP3\?&_O!5uV#nD`Eyvy<s=Bi*HZN8HAb;)sjc}F{9P2=evVmdd`Ks+aBDY4b5fa#8YhYVD5g)i!{2#RXF\?WYMas1lsue$cGI|n@lJGOXLk6RjeR{g)Y*W*qM*bPJ!~HH{{wu>)=n0j98mTgHIZ&3OM*h$xI)mVZNh>T4cGGj}tNZq);~bZ-I_#j>$@@oI5q>(1Opvt<Th&SqxD%&tpqyRz8VIv<mMLL|%Fr\?%`o#$K-73(Wj*8l|(tWN^yJ#$G@|C*7;jWL>3U(jf=`Aiu@9eFOWEINFj~OvE(VkYycC1mAQXEFHGjmXg7htI+2di0ro0BKA>o9\?2%dMD&MzO_NUOl_+TB^<JPl+I`6Zr$aI<x_c%5bQTVBf<#ghL=>gx_pvwjaMXC15eEoh|qs{8lbfr\?M#y+\?X>7+TRj#Uz!lnqWu0TuC6^#`{y_gg>Ts%wfO5MRV)GwDYgJ-=`#lVS+Ez%r)5_3gSAhhF_2a$7p5&+#S!eBzoD54B@66JZ}Mkkr!;ha0$O}9;$c}K+YiKS+w+TACQt0hgh|d!hi%\?Dtv|rtJiAI8(D!zh5c0>}Km9ON24)BThvHajlNUM<6m>PKV|+An5=e6t<98ECuOJPdu_{>Dm2x7*WC<z-Lq^oYtmWC)dJLtd4K=o)GJVI@Mu3|8x2bndM@&xxtX=0zs{L|<;xt>&>kjo=%Y\?nhfAq7^R8<4CiP!~MuR~kwptOJxkg`|YjcA3vaqTh1TlJ_i^3hvSXs(-BWH!eD+FO%OC$mnvfWI}b;xp=ml9Nl`!h`EMB<^9BE=cZh<jD#wM-Oh=TK|F7q=4wExsT*bTG_se1kW1+hK^bz%A<tl8Sn&!FBO%l^TP<mUPN!>y;`QRPv7G$gzEY9)U+\?U&U2PJ2B&mEst!u9f59V}<l1M&3@O4U8rh26qrNX@I59rVY-$Ull+S{1JOmS0RBP`M2}SixS~HlqHL}OiF}&_{Y*-A$NuMw@q3CVYdjoqQ6q\?ceasu6G;~}>)pgo*P)+m=Oz453o>9dFj6WmMJOJeH\?i<IAYIVuc}O\?ZXm<);i3;c`;\?mr5fyu-F<ZjuqELT~zhcQaQ%7C33\?^nE!)yDY\?@yS8{F;Mucdr*C~gsl6d)#;{2Fu&nP!v4&aV)+KHjty56YEMO07odp&cg)Cixe$L29beVAW3E)ZzWtE*Q8fCnPk2uBw`xA8TOV<j`fT_0a9\?\?eGzljQQ#r+tw+)8siBb1Mnc%J3@%C@sd1#ZfRQIsn0EuA#<8B-`m4VmB29Blc@Cq1dVH))UR}R89d_Ow7}RqdejT;i6{a#{Lf-Z6;;E;qBa7=G%~noh~V$we5`uXgPP5Z+N4>uIRT%U%}#DuoQxSnd\?PsOo<Eq#W_vfWSKf1ehCNRbw{Qr%5e>4)!$0Qv^N5UVu%n3wku{r1n@qYAJa9}5z7595(#+Q!UGu(8t}-*n@>kyKC2ci(({5qbG>Rw5SP*+Vld0I0qlz0{v)qF9cQHD1\?L(tz+o<AZ&(r`*qNw)d<=IXKwdNzqdhb>q0JV;jHf|T%ZnsA23p~5UI#0^_N+G\?m-S>9NP#WTq&O2dJW|&(TRw\?E^MK>5Sezcjv;td68GWMttiiqCV3&7$5>D$(svSPlJ5ZarLwLdn&+vU6#k0`U3z#t`C1QSbrO^j}5J^7Si5BAv5Kg-<W-#DBl2phpFSk@x)+#=p;Uvu%78t!DVFn#&qs_Bc4NWikKOU~+`^NlNveRsm7zc@kfAQmR6DzQIzuL4SuAV2fzC<NdtMyXukjlUwUAzFdh#hVzIx~>tBgG\?*FMzs0lo>08qJ~AE|NKJ&!5VjP$xgsR@Dt56&vm}SGtbQXN=r=&C1PF^mpG0GPam6^FRDeorYjx$O5B<2LlCrboC@$+HM(0_@2e@9J{v#AO9Wd#^i~WtaMD\?kn#N73kx_0*9kWH^!X=3drPPy1<g1hvS~&g1)ATr=ZNlT%NXl0r|9){4-b=xSgfOW95rR`iuumUb-Jx@}L)Tgg#5i$8(Q=ks$Tf_F40N%AYfhwF>|%u%zU2}_3BR8TC{TqJOPF`cm9ZAAwRs_v=~pH&hU^ZyP)0w@&%-l^fihx3U}>kiB5b|jl48;|aV(Zq1tg&n*EU&BZD)`{lWFOxZEYXSwCN65C((N4f$KBT*n`Quf<<<mi2oB9Ee}k8NBL&-T0C*x5v7z#{!&hs9^DLw+^_C~d40KZA5{>)<>ei>lbyJUkpX3*t}^v#$=d)`Gl4TCG8BchS5-Zu$PG+@K~yS>k&!wJa)`@Nrs|FZ^R+e%^PmTvTr5Q{E}UtUz!hnn{75pwi)23nH&3MQC`qz-LcMh|lRMgMuYSu3u<l=vkAZ$~9~fb7lo2#Jd33_|4HQedi5woZs5p8Avm4+%Df=63)JY@i)d!k>B\?2$t-<6SRd{\?|kXWSRICOd!JD<(j45\?t!Ra%3F7L*ZqQwcX^88)T~NglgBmVJ2z8yIJ)V!Sj5qFjH#5svdWIKyyi`*o*|xgi@wGj$z@SndS*C9&>8yf|s!UL>2OvillBieXcexHoXv(#;)L!U7mY{h!RG`K%mP#-9G<eICagA%0U|S!pZ~040&`8D(MTyM8lPKoBD!2si+HX7j=E3qq{}+c+)aXWn19jtfIG^XyoizE@k`NMhHGd|N9+MuqYC1(M-4PT*|9n)@=MlHH>%jZ9rwY0X_hCQ36<no@yE<=QT<O0)lUcT@^$P(0xLmsSrHm=9o|;vtg+KM%sayI=v&3-aO05wW+S3+pBMSEeJ0m1Js#h-Rl8qtXi~AixI<#sFJ(=L%R`ODUywWBrxnT%OqJ_6~YoWMC92A^gKB{RRVUY^kh9iL)JOu$oAQ%@nNVvlkc$>jf&5S^WxBnl{L=XjaP%EA~m8)<_rmYe&BJe9PRt6&XudzEMnjZBsB\?Qf84xGB%i}`<5OcNWrdf\?R}HPUtJ|ad=D|zBYyT$l2`=^SQ->GWFAgzoYeOxv5L`R76\?l2Kw|LQPP!>9IacK5x+xt(^y5&|v{b2{TV^X4<|C`Anb-ZRH$Y;LPC^=RUk&O>|WI+2i--08Oc2}Ivm+KnWqo@cZ*!8J3eDN0cwhGWK-1gQ4yv~{_)&~`%uK+17U%7VaJinyK+8Q{F4laX|^l@-tHMq\?J=y9pRb9;JM_B`\?cmSeF5qrh~3Idm`nOVA}e6Tg3fuI!1c#3+Sz_MntGmLkM_-0!owMK2FK0L~BMPqFffDO`_BnCvbULEmDKDaVI-%dknRZPY<5A$ar-Z&K}sU8&*OUqCu|-B=Ybr2DS^9HPdt0tr;|13glAfhF@T4zH1(`Fxj)%p_*6PGncctfEsuP`dG;`*TATs*Wd)yawF98PpQJSKK\?MBmN6VkvVRwko~eSD$M-r=2!F{K>_kO`tgTLblRKzs)yqr`edI>i;3EK&Rz{IMiJ7jO7U)U*5Cm-xsup9<|Q$3BW-xGjI)-FJK>({C18J>5*HTPkqT(CuHHfveesj!$f<13{XWs};rAq-;Hr}>UDenIfxv8Yb!qIUk6-IyG9fyW3`B3L9<dMll!%U(u&lPvczTN-Tcs#63*pk!K}>vqk}-wnk|t%2$Ck{(P_K$(U2*$+5v6WO-\?Wg|z(ZGKvxlA4(u@dJD|Z!RRMC)3X;nQznU!00XoXieFfMIZW{YmkqW9fS>h=7;FOg*\?\?5Kgu-x&=tQK6^0",
"vY&OZ+\?TjGY9R+>b^yk0mYa9|l=09}mhO(wY(5L\?{;vKdr~1Rx=;+dCbq~z61R_UB1uy2U030+WZyFfkECTwe%&F6`Z{>PCAncoPbvyB\?ARFf>aP1G@5rRz97V@{CIjx%<g~0ipdGTBajz2DWdUN8ixj_r9pSPyLd~\?f5)7a3J;}rhInQ>%}Shwhc#V*G9\?xbX3vK(Y7*9\?3yA#\?rg$ty0}WdK_@{DrfRm(vEwu(o}<oA5piWFM1dj8DB=Yw\?A+KIvMGSIw-A#9*@51QVzI<2^nnGPy{TB+X2&hTjnU!GOtjfC};k6)fHkA^{sXtp;JURK42wGUX~+Wtf1hf)hX&HeZAcy6BFHL{Z7uftdcPZCL94iafCY>038ydg%*{aq$hybO\?|$kMMbCCR;BHt!8JTs#|zauYf(wre%AX#vGrGt4>UPJeB0@-c3zQCBw$`i5+s}YA6Ynczk>lz4CZ9MCg>K9&csk)b*Zqp}Rgg06)#tt6B$`2`Ck-VM{V<rICH7*xPzqyndnX$<S}JX~Uu6gm9ISj&iU*Y`y^9hWbd3Z1+z)tnJLrn`$-U6V;jfU5`Ab7ywO|nait_+~BTErFYtbK&)q+s\?}+ay||hq!p*0Q+|1A~9!qzyJREBkJ-svt)X6m*DmldskKl{8&4w-ey4{U$8%2s9Ea*MnB8>iudv*x<psiUVqzcwEm$eWX\?$AVD7~n5&ku+Lv^$xE9@Z!KGCV!INx0!5}O{<Bj38z<(iiEmslrW{zQfza%Jk$V>9h_RZ_p\?bA<NfjsgmTiRE5~;)j|ep>d&OWURL^5T%f)t_W2qX5Z`\?O=6hh%Oka(fi1~`jB@7Aln93p+#l=XG)_7>yEraaRSI3qmL<Wyh$lT1jdQW=ByAPj51rwo~xKj\?0>3w=Yx9Ijkcj9iLw3$fxUNCHfrh}&D^_jV*l3Um^aE\?uo1fky^j`BHvOdD|_o)~6CAS#Vc(v{>r$wP~Cr_T9fEt\?H<MF@^4`^h;Fryjm&#bOMS0O@ujxWVkoxXi+B3T-CGju|W#_-m0irm@zw\?+dJY!#6mmnI\?U$Oe3ZL|@aM;6`}HLMf`yI+\?9;pnZzaiw!~j6Dn*K3-<x2nXw=APh;p`Nhf@k9-^VxHQn1FjX!n!Ex<PaBnxjDC`6wm@fUkQmlVD)=M*V9lx3pJ2&M5PZmalH~7gxB(})>eHxu;CSIL2NUIynV$dC3U+v)`8B)`U5~#T$xicF(BATcuvkqcF1qo=9u4=gpjU=<qmb4ajo~zVh(*U@*<ncIrCt7n@P8~J6`ytblivIIy;2~J4rj}S;MlFyA3eMDV)^Ziw+S=R\?OyDKk!>>-dOKBs&HNl\?d#L1*OZ|J>SPbnrQt_yzbPmu&0g&>a}xHZ`(VrOx5\?2G$^STbq##P@rh%smNTNW9%YaL=&ig4Uu-8Vay3\?eWl0rc>Of$T1gwYNQu0iXyEy`%Ozniz*C+|$G+gr*#dc\?hV8w6L)d#~;>;t76=#{gs(ZWAHuJG~XHYa`p7OU4m`j*TyTGn7ls>_h+!w2kRQ%6QC8VwWOOCbjA;{Mic|z(TBYje;6\?*k^3x5D|1WmwDTy^p8B@TD|a$z$I~vZ+quk_AwszK_\?#jZo|YmqPjsiDDr|^o%H>GydL*23wplB7nyaoU(XylOi0$LvT-NQ4R2Q3{5qsryEWT^Xsq+6afH%l$q#Hd;8|F**t1gBy@t3f*+Z&iwFgd=sebxDBJ^KSeY`H)IB~vGQ=@Im(hclb9#Hj+zR7~5!10wMAa@+_eVLClTmZBUJh}+f#orkj57H##6CO|kXr-xmK!H`P4Ya(>J9#g\?*T9iY*NJ-MwV98Yk9h8|3xQm-Cp=UR3m}591zL~-n6dZ9%N@LUZlaVIaeDoxH3d!iDH1;PBd6Wku0M@v&S1}oY8PQR#3ug>6LwF8W`kKP0c+X\?OVM((>>GwvW!2j\?OLVsui(X*rq}ecQc=t<D576YXP{F88=nyi0c~}f{-;l!Bu$4D1gxmF12#-pEh1CRF+iD_BCiXJ19BxWpf<2RutmU#C6lpt6yX!oQ6f_yG69s\?!1+<%#Aqo|$Ak4Tl9Xqtw^b1pvm(Si^YjMSa3A\?Lb$z%rq`yfP0YOv=TS<gAk)~p)>iUZWM__6pZN5`uEFDpO*@D>etxw#+2jRYJBE*&+}4&o$cUeMXmB$G>$!8\?HA8h>P|Sod1g>(9wCXLf*hTM`-Y3N4NZd>`kGSBY>KL#S*|6+iq_pw\?z(L@^HEQAo6}gY6wJ4Q8Tz{nbCzVk0B)\?$JeO4=FJf<96pzJ&w&ny$i)sR<5pXlLV%>_WwTi!LyJ5e7<3>gn`AZa846wk@<Pp+Dy(!3_N=X%Hzm({R^ulh8H|X^80_@_$PER{=lLweNDd}U>OSAWfqo>x^Y>Cn)#Uo8wM!fWUVGig;<O*>+IYPM\?ystwNx;Ir+la16W~>SbA~lX0!^Ow_k9_s5K}O<4^da{P\?k*%-R;5wa7<)CeFoH~v94v<16fDsjB*^#QCXD$H*yL|ZF`<c)jIU5tDMSt{yiZkFqt8naL>Nkkyfld-~CPmqz=-6E&ehmy`6lfm-{jZ2jz7W3fnQ$-+_Euh*dCdzF7GUhA{}Z#U2&nj_is}4nMAFyNt-ju}L70B~Sc|Fc#5EcVIseafyjQ<A6Ab>=heid*|WU=El`3((UV#+&1rJO0OJ;qLvVAKf8*&r)k_WV5=*A$H=9vmF9g#Lg%4b&%3<Zt@{5@CE8Vyb*qWu%m{pX5gT>pp8M$b((vzh*8Nd+_z5*^xB~MUjPkkVDqX^kx0vXi;00EAxWX=GyyCm4Gbz<#d`7rCu\?jBbsC>s4&BebJ;v`k5p%Q@re!#W@<!WM6lm(g6{2P#g+mj4%$7Q{-5Sw^8u_W(|`Mu\?WCla1)fC\?7t+E5mi{mb\?q6s*@5E$P%;#6mHe*cZi2d\?E!TaNH4>n_25fl7*g\?+9RED9Yd1Zd`lPxOEEiVBq0ME=~^Tp7+UZTj`D=G6T!@o`;3PET*Fv}>hG@il7WZ!4PW}XF8k2Z-tdy+TBLRP@&;>dqW-y*S^>bWqIJK8x3h_mI(k#Ef<rQT_P6RO`j$h{vsKkskBMM~V9k6#s&(OV)tNPbI+MIj*Eqf>IIU$1E_KGz=iOH8Zso|l^R-mqy6+*V%+tSJ2fOm<u|{P|ysGO~q`lmslIBy{Bk_S-*>c3N+pjE>3@i}=D=8Z>pBoPh;j7J6pnB)c#r^@kfm*&2`ku=>L4\?L@bf7Eh%p{V_AQfML<odcuzm75|Nj#EmE(&YtZ}+(u{<y79!SeK~<\?t2zkKLnVz#te%4W|\?XbWHL#G&U(4*`cKr&fEI(Ju%)J_VQCR@@sP%d_Tl>2MsX5g++|}(1w_`yn2@mg}&7|_<F{gfMB%pJMOPaRv8Ck^JU7WR7IZzgavFt9CU@N4Xziw$\?Jj-3m%*=B}|@Bawvh;Kf~gafy@U3r4i2%WTyp9TzCy>m%ZVBfP9GEZi`V@k!CFRXc@qEH\?(ygv~LV\?XVNE\?8pf`_hPXfAG)E@9x6p}m+C3A*Q%S_r%)B1^PGuEVy(j`}0N)j$R;TGOB#C&@w&jHhN<k1+)kU\?uN}sFM;yfQi;GFTv{3EY4j;ri-snjWs#8+HJL;Dlp=N;p9XIi~mqOq3+9x#Kh>@0p|WER}0og`TKiM#&X8-z5kcl4b}yASlB_!M<l{SMoe7>Gpdb4XYXVHbvbG>^BdM3<vG6GJ~rdttaaY%`wX-mo\?p>Yrl`isNpl77@W(as#pUD<>VSytzt^Zs)(!IN5mOfp~1Vcy)JFX6^@;ml>v_D6#O09LCjSoYLbCl2r+z-updJJSDp{t>g}*cpmz=-ad@2gmi~Ha%B{EWAvWb7XQ(lHWjtp0+3Jn01HZr$^KChZa$3cTvhKP=4f@vK*Gs9bc2kMy`*43_\?AEhz5\?}s+jgV|qO*N31Hop*uHXn2)\?8RWt8AD5m4ttmD}jCVevxzYbO#rl#djHTauh6AFd1te+gsk{Jm4Mbfd~P_1{rC1KrJjaHKW^Q9oZTJ!FBTSB~znc6><D;4KM6+`x;l8Am6kC`z1GO_9+GG1uV4V@PJ1s@zFxYmuQRf1P&j*;>&$L5}r*X689l-1;we2{||-8wo8&KyA%B5X^+1xKS1JRQ(NPgICWem",
"JwX4LaGg0gsRiz1Hl%l_yQ>d*Zg(rlj4k2`Xc00AR<k65g+-A&Av8^T6&&X9^KWe_dz8%Q>z<LvEg5=tmViZQ{35QqD8@gU+1ddbB=ye{JT0bQ#yceDr`h|(zT~OwPK6}=)t%E=bMKBBwjsmeNaE@5dT;JYcPHSO{o*CS$4B&;dWn2Ttp@$b$A>yEsb>nx`HQ#$T9y1favA^Rj;KfRtuNBeenPmx$j$}|ig3a81J^1rq4T\?xs{<ph)ad7YFX#}sQ}XIEO>jNmf9EtHi8Jp!$28GNOi&nL1YGr{P2%l6pVVRM2tl~wL|cEQnRREC>M|g@AM|k+Anwj{9XTzB<>eETpp$(PFDDV$QeuM&gHTo!($NcVX_ksl%9fzt2MuK-U@x1$Xy-~FXjOom>KbO3+\?U|@^ZYme*H%Z_]",
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
