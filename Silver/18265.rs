// Generated with https://github.com/boj-rs/basm-rs
// Learn rust (https://doc.rust-lang.org/book/) and get high performance out of the box!

#![crate_type = "cdylib"] // On Windows, omit this or pass '--crate-type=bin' to rustc to avoid DLL creation.
#![cfg_attr(not(windows), no_std)]#![allow(unused)]#[no_link]extern crate std as s;

// SOLUTION BEGIN
#[cfg(any())] mod solution {
// macros

use alloc::{vec, vec::Vec};
use basm::platform::io::{Reader, ReaderTrait, Writer};
use alloc::string::String;
use crate::alloc::string::ToString;


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
    if a > b {
        a
    } else {
        b
    }
}

fn min<T: PartialOrd>(a: T, b: T) -> T {
    if a > b {
        b
    } else {
        a
    }
}

fn swap<T: Copy>(a: &mut T, b: &mut T) {
    let temp = *a;
    *a = *b;
    *b = temp;
}

fn range(start: i32, end: i32) -> Vec<i32> {
    (start..end).collect()
}

// starts


pub fn main() {
    let mut reader: Reader = Default::default();
    let mut writer: Writer = Default::default();

    let n = reader.u128();

    let mut l : u128 = 1;
    let mut r = u128::MAX-1;

    while l<=r {
        let mut m = (l+r)/2;
        let x = m-m/3-m/5+m/15;

        if x==n {
            while m%3==0 || m%5==0 {
                m-=1;
            }

            writer.u128(m);
            break;
        }

        if x<n {
            l = m+1;
        } else {
            r = m-1;
        }
    }
}
}
// SOLUTION END

// LOADER BEGIN
#[cfg(not(all(target_arch = "x86_64", any(windows, target_os = "linux"))))]
compile_error!("Unsupported target architecture or operating system.");
macro_rules! p { () => { "stc" } }
#[cfg(windows)]
macro_rules! p { () => { "call LoadLibraryA;lea rdx,[rip+GetProcAddress];lea rdi,[rip+VirtualAlloc];clc" } }

static mut PAYLOAD: [u8; 2195] = *br"%Q$$,$EQ$$0\GM%Q.QZxlhA$^-=TQ?IDQ*)@nj\XlTRe,r'9)K:v9c[PdJ5j)[?nW?}kZg_])p2j~tAAiSHXaZHC%iq}11EH$]Gnjv]8+QA?IW9:K7]2hd`6C2Qmo^)N]>0;B^ein4].%jPbw&=`Auu\^KS&.[Ju9YiW.6*[*%3\(mh&KnX`P(3'JC7-<$Lue6I1B_+d.[|aN?bdK*'R@-{nd@LBJ/CdS-}(&WdTeZ'aXNs?bD)]Kvom<D<F25vp(1Vtv3)oS_gJF,|F59z0orB{@0E9_I=Lj5.Za/ocZW/m;)G=`KQyWH[/ioYd<z?mK+gqsUKOZ?4.hr%ax^L2Q3MSF5);GpIp65l$7}K;(ZNz/aWKrsy2<x8NS.tPFayXe+jlS'u&-q|-WHrU;o`1/N|a7>S-,l~CuDD8Q/QL/u8^mULfQEckB>YRtl1C6JP;4ov^U)g[rFpt*7NYw07jSb&JZbfeSw4b5(jgk4Gj~{C*>}8'3:;_i0QUcj.:xb]8r/*K|285%HdDQ|gRuLJ%_C3o:<iT]f|fJ4`%$Q%\Ovvglw_Z$1pHjki|xP'>RCEo$Tygc,A|+Lsgjo;'1m8HxI;'b]}hbfVZB)=dvH@UPK9:itCNX_C?v6O-.ys9==}y}vrz(dnU:a*`%PrwuDxcTc%Cri(saH9>;4VIjbK?fLXn>ZG$[QJIa7>Jb>YAxu,H=AEDwk1j'4&s%@jM2i&+;<Inv,)3Jm$~Fjt/5T+JjhMp/aubq;vLta_ICV]rqC=m<}03AvbAv--hQ>%k}M{SCEiBOh&UspFOg7jC7}zGDRD{=)a<U&Yg3FB|RtmD6%;zG5_=h^){JU>\7`Yyk(kzCq*t=79/VW-WryE'fIZ[Z>~Wx*x[iJFm']7y((pc-*}hDXQe8TcZ8]gEYo2zBk0=e$8'h58Oup6'`>3g{s{fj|``N<X][W])b?K2.a%'l;flqA=/<Xs00y}>rsTzZs6H/U~0a@oj/6aD5u>k{jUE-6O}/9io1T84(;_\ss,R'\$+,'Kp6G&/UKwg+R[F1m0hT>A\]OGkJ%e2\FoTsW}BiI&YxS5qK7amM4^K3DNnro<]T02K4.F7Zwfm_FG>K3onTAuT)s^qI>f;:%@C_(,&9*QpiQ'>>SOQC.FF2qsD${aBK;Dz6^N=`U0JCWQy;.g:DqP,?i`PrW|k?>Br)`K5N),{Bg6=-K'a{`?KYWn4w-,hH@6gF9|ovnMVpT%-Y[=AQW{cFlI'U}]69W^aDA8z@$kVD}1Go3imUpjR^Zd5/J4vJoLI+)n)d]&-|\(rD=@B.(ZyoztJAc%qJ)+%2CFnzxrCX_H&&4/NuPb2KOK|O9nxmHJVu^s/UnB;yoKbrx2B}ed$PX\TaDaox/CUewl@<S.N5g;,DXZ0eNkx8PFj,@=N=|+I&Rf_e7Nh=r~:mcLL<SM,yH_+s,%\{GDkheA;6&gO}DKrTd;^0;{H~AF`rlV)jk`,2yb7Nj`PLQ@Wz=>O|hAWE>1e'\|;hEm>F@rOxGs:`$%VrhUY]upv|>Cgi$<:7&@Yji=lBKMJ73X%$@=`8elgGI;8A,s?Me}Ly&wN/ZMyGC%>f1;7TH~aY3;k*jI&QgUA2zmCVfA4?&_oImv1Hz+@fz\bo&FrvXSi05}+.?[.8G2yR>>-rF3Z3sYIkf'zL'tQD6kv;QWlBnPQ9BUDosP&`hYo//m/{F9sbl$N=n]dr=+L,J2R1x5{3w`9McP_>_TBdu9bx*mO.w/[L8,*w^P94T2Mt}2;aUqGE_e'se/39tW7KF([f5pOiVa\^Pe;j}P6L=7ni1/aiJ:0137D@;*56_54qoC5^jT64j]:;4)l~,]Z]D??~q8caU8&23cB8L<xQ&W221p-LPG`@k0[]KGQOb|76__sci{'~Cd:t]FEk>XTwN1:]=8Wg@o(i[F<=VjM4o*iIme75J=AwJI?p8AN:s/-cMg;'g:4@&=81Vkha[XTXI<@U9cvX)a>;ZvNK+@Us:9<.4]DKI]`{QFq|`7PkR1QJ$f16|B%dP=Ef2LWj$gH$j\\qYaKi=FU{s2h:ygTw0]'__;^yS?|o{tTp:SjZ+G)-{[[,+_)Q>Iqkkrsn5}sw-Us}YJBYjXH(g~d;'rI'pRBrcD*/j(+f_aY2bKkHL3dPDe9_/[gWN-|7taYYo^;gUVJNcgK03LX\c~Brsl*6ym?P8W>K,;z$$!";
#[no_mangle]
unsafe fn _start() {
    s::arch::asm!(p!(),
        ".quad 19510173000030c8h,4ce8d9f7c9h,459927e36758096ah,870d74ff8548c931h,\
        4100003000b841cah,0b2ce8956e7ff40b1h,41ff6a5a41226a07h,0c11fb0c35e050f58h,\
        99f572242cac0de0h,15bc06b242cac92h,10c4f608e8c1aad0h,5052535be3ebf775h,\
        20ec834851c1ff51h,0c93197485750d3ffh,90c9d0ff585fd3ffh",
        in("rcx") "KERNEL32\0".as_ptr(), in("r14") PAYLOAD.as_mut_ptr(), in("rsi") r"-n[b4n2|3|z+6|EI_'v:ZWHZ}\DWh'i'j'd<^V^VrTubU$7?Y`xGcbG67?Y`zGA(ocPYN&)$,$;/*]fU\)w$1]]T8?j]Td~_hpAtUmVHd/T8d/*>Va^h7{]uV7R+'_N-pX@=MRg+uQ^8F|CZWSm$0@^VyMR:$$sd;;>%g|50;BcHEN[?<ko?F-$\M=MhA)L;tO@'Zg$$]<GjL>o_Hxrois1&*9%QaL[']h%=9hS%%|hXW3~.ns2>N1;;1=oXxbVNMeb=^iZ4n]V8w{cl-A06{{pki.9^XHQq%Q,$])cn</advVEQ--TY'm_sbV5Qo(Z3OgQe5)DW''DTL&UVFdvyE$3);)2dRg0pT]xlW&q&$$i0:Kv*s7Fj,TE1(Q:/$YBNG{jQ?@;29YoT8Yb7hE$Y0p$[8{FSN|%JY}J=a<$$^V4m.w}}*dyB;t,`v^LxRguWe|lsoLEhfVL(n]^l$QX}b<At,V'$,Uj(irn[8@zy8U|4*+x.&/UA^)xbi'A7RgrTvPFdK6vb4/GR]1LZ't_-=h*:GDya=$m,zy2n0]OIemm&5V]?R}i>H8uWL-4/bV)>_}\?T}T}-dAS]+2m{h\7N|U{e<of$~]V|sME<kplL;YkG=L;WxoD{h~1f-6ii'W}s<rTIgFdR=g.caW)<7\)69\s9q]W-J==DY6)4Qjtw&0XZ=\)hEVlDuAH$~XuGID0`@DkPh:-9hcd[?x{C*q'`WPsHy(%1&!".as_ptr()
    )
}
fn main() { unsafe { _start() } }
// LOADER END
