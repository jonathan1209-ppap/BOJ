// Generated with https://github.com/boj-rs/basm-rs
// Learn rust (https://doc.rust-lang.org/book/) and get high performance out of the box!

#![crate_type = "cdylib"] // On Windows, omit this or pass '--crate-type=bin' to rustc to avoid DLL creation.
#![cfg_attr(not(windows), no_std)]#![allow(unused)]#[no_link]extern crate std as s;

// SOLUTION BEGIN
#[cfg(any())] mod solution {
use alloc::{vec, vec::Vec};
use basm::platform::io::{Reader, ReaderTrait, Writer};

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


pub fn main() {
    let mut reader: Reader = Default::default();
    let mut writer: Writer = Default::default();

    let n = reader.u128();
    let a = reader.u128();
    let b = reader.u128();

    let mut good : u128 = 1;
    let mut bad : u128 = 1;

    for _ in 0..n {
        good += a;
        bad += b;
        if good<bad {
            swap(&mut good,&mut bad);
        } if good==bad {
            bad-=1;
        }
    }

    writer.u128(good);
    writer.str(" ");
    writer.u128(bad);


}
}
// SOLUTION END

// LOADER BEGIN
#[cfg(not(all(target_arch = "x86_64", any(windows, target_os = "linux"))))]
compile_error!("Unsupported target architecture or operating system.");
macro_rules! p { () => { "stc" } }
#[cfg(windows)]
macro_rules! p { () => { "call LoadLibraryA;lea rdx,[rip+GetProcAddress];lea rdi,[rip+VirtualAlloc];clc" } }

static mut PAYLOAD: [u8; 2117] = *br"%Q$$,$-Q$$0\GM%Q\gZx>R@087kniwx=C9Eoc190u&f5j\k[\O~9*6v&T*~Z5+z0?A_B|u200v%|0X+vMA$|@;E0Vc_+i66'Uqz?o)psBTL9eS+Eb?LY-5^CM5Be-0W7uH-.)uG+4uOpL=Da>}o)oEJ`~K``rN>QxK<A$R+ZF5U[,KO'{Rl'$ABLrW47t/UP&2Izz6&sq<Rv1uwuztm%}`4||V|[UvAgE}qEG{EVcT=MzC@?9RUO*8(`c_sW)mxfv^`;>=}cHoYIh)r?._QB9ObeqptzHMz3W/]fweYL4AJv=&UpmN,nBHJ-Ti`%,5e*Gm^3HRL)wAaM~$prezJx~CE-1](KJC^C)}`o:TFVB]$oI897[F~R:3W*>4<}I7`gUm[3K[<=4wniIhXJi,P/ieKkjB1W6\`llGa44&Z/&FJ^jL@HKWC*yi4W)x2mn`(UpsrnT&'1IS1w&{Xi=A3*O9ymuTbEEW?|z<C}3&,C$7EH}dA.6cD\SVR2Zt@7he1b[6<)U/b\y}3VFWb5?'~N-j)B4EyW,,3T&5O,*lmBDWbEp+cvImu+%15J?l'S_sHvp=$4q?_bN14SUD=UniAG|o$vco+_vy{y%S]{Yv@+U5|W)O3l^9kziaTbut$PBJT%h8~&y532:Paobh9\$_[wnZ;:$h^'zD<Oqq4I\4ZVhWud.%r_U[PS}e$Bt|@Js*]yH;<Yft8SRE<O&%g*A%blO.Wf+[1`G+4Jp*K**@NSzD\ov{u(C`je'd|Ugdt{|0^%&CU1=y27\\{0qb'Y.3E8^`:9U|w%^$X|MFv1Iwga_VqrpQ{WN_IP{u2kCd[E@l/9)|+c]J57u;{LlOQ|4]?Ba?;g:pRz{z@^P?&K<q$dYY>J=4sw/wr-IP^Uc;hA3@UO)xHpcacWS.I;he?3fGxqTR7O)6syj+RVjt7g0w`K]Tnz*Kx9h*Qh\(s69,`%OJ~&fviL0F*Dp$o\PQbl_eD*Un{[z'j6Mx~Sp<9wZ0@>tz>(]iQhMfad>OdN2;Y|~xq@J<l8_'DjrwA7Z..U,JMuMaFGFa${/OLDpl?dse$Mv)^2B<o&QDQ`M{%n;4zD-*M/:zq8)cd7'*2|s<m7r`0xf}{s.b{?h]Dgk-Y>,4@T2vgm}7\<sxp<6oGO)B[pjU?5UBfo9rT4z'7%ZXk9`Me0)MEce(7Kd}R0qy$432e-+zF?iMWnD+sC,]z/VPV?OHK\t%&(NhpSg}i>qzK2@|tYW8TU>_g_Q]qELcJr4Z=;WcqYa?Lgf9?QHC^I4Eu??or=\t8a.f5`Ia9PC]7lnRt%JIZ*jB8u`V`j6wZZyj,+-t~?eKgcxaDl~s%E^/*3E*[FVXMH)vOE~U0uYZsI~PenB(y(3`W/sVr]k@wO%p?H^Xo%v4Oj_mGt}.@7<h;]'Sk&Y%xEK_1:c=Qk.&/Ew\6{@KzbYCYrJ`NI7ZC?JNGmSzN38^1+.^IW]e^.Jnpt^;?:mdH8RjZir0p)WhnbAl==jwH8uL38]2t_0s=/O3rMgDdqJroS;5VRfe6HVwm],e^7H{[TSnoSgM:T]B*D-cYxXQR*oXbb;^?SoEs/k|)PPs5,`|B>_pf^/lNg0xolmg[}B83XlnS=J+WmcZFkz^C;4wMZB0nzoOLebPW}X<+*G8lov5)O2o3hs4W.9pE)8`{.`)zQeN9aBq^i*4LKUO\:McO'kT\8]'Tl5}RQbAv5j&;<<?XS1bZfWd4mVO?Az8L/[{WmJH*N-5KDPPn@yo30:uxhhmN|x+5O6?^xz0O<|EYp\3=^_E,aBdiTQab`Dq[>Xjt%D@(eB%l1KKV5eD[$,hP9]S'Qi6wxNq[*13C499kJP+;CV>{u7+LZ5F3TIMo_W$l;0OW.t/0L~5:4'_wv{mR:u@Qvm\)[*$+/[}&P]`0n5-XY-bkp,2ARZ*(&tUB:/9UftNk'vb$n>\wem&f:Y9-/aDr(;ULr.<xrh6]fWk`21{%jsr4*PjGVF\|[gvtrxe\'p4,EQ8Brpje\X-Mv$dg:gHM%+IB2U-zC`D1oy;{ggzPR?mf+i(:@SgE-f>>B?S`|[*8e$W(TN]chP{bm|6m=a`uDQPC8lKe06.zNbxT9`H=oIV,1qgE^Ov:{~)0m-9R(!";
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
