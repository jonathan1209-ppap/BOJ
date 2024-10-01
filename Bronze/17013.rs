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

fn swap_rows(a: &mut Vec<[u128; 2]>, row1: usize, row2: usize) {
    a.swap(row1, row2);
}

fn swap_columns(a: &mut Vec<[u128; 2]>, col1: usize, col2: usize) {
    for row in a.iter_mut() {
        row.swap(col1, col2);
    }
}

// starts


pub fn main() {
    let mut reader: Reader = Default::default();
    let mut writer: Writer = Default::default();

    let s = reader.word();
    let mut a: Vec<[u128; 2]> = vec![[1, 2], [3, 4]];

    for c in s.chars() {
        if c == 'H' {
            swap_rows(&mut a, 0, 1);
        } else {
            swap_columns(&mut a, 0, 1);
        }
    }

    writer.u128(a[0][0]);
    writer.str(" ");
    writer.u128(a[0][1]);
    writer.str("\n");
    writer.u128(a[1][0]);
    writer.str(" ");
    writer.u128(a[1][1]);
}
}
// SOLUTION END

// LOADER BEGIN
#[cfg(not(all(target_arch = "x86_64", any(windows, target_os = "linux"))))]
compile_error!("Unsupported target architecture or operating system.");
macro_rules! p { () => { "stc" } }
#[cfg(windows)]
macro_rules! p { () => { "call LoadLibraryA;lea rdx,[rip+GetProcAddress];lea rdi,[rip+VirtualAlloc];clc" } }

static mut PAYLOAD: [u8; 8235] = *br"%Q$$e)(@$$0\GM%Q.QZx=R-J^5e'M9Nyc@XjQ2:uRRJjku/hDX042;E,/@j(ZPI4g^5^t.RI~V%0j@(.b0)B[j3ssJ8yv<DWBE|K:Nfpf^S%C0wof0ERFayXqf'=ay<:{{dO9'UW($5w*e*>3L2nP&aXwelJ8O`<foK1rold-fy:djV3&I~$[WFecSAoOLmCtUXe]84%5b2>,?TgrF=520);JJB@;bdB8cf\-M7^i\Vk1B77yk/e6CNn?Ybg$+(CHL,U;b@;`|%_~BJ[n)XunLKfQ5~Z'Eczep`42{FTtP\A5dud[<%Gdv:oB_~A%Y'i7Sn>/bQ)]n:*k9%In0X0xogDwgNi:^E^H/37^v,K}qso,qNrfE4'BL%59ybBf$@rr^cy1EI7;2$&4c?:{cH>.22r32||e^0}wWQa8+n.N5+Bo{@*X@o.hQt<[\WL]d).PRgbAH^;PRhgdpB9&D:8nF@R1?|m]YxuBT(Vn&w/%`2e;6RFZX'@Q%GI**e&RT3<kqw+-]X^J_|c8'[z&(0)|<N&^X-DXgVQXJgnWRBQm2'ybmPiis-KCjjC[(Bv,s\0HqOJ))oC9Jf*.3m<O-4r,7A*S59,|n67o;XYYa|)-jJaLsyMp0VB+2+&&>W-A<ppLzc.D+IVN*_]+PsJjunp]fEoE](s@/Y6odF$qx`^7P9Vn:o9DX`\_|9b+dLZ*N<Hp|sKi:4.>i'[qRHWqcO;Sv]IAMKO>:)$w'k'&(OG@jv=?M=T}wA%QB&Xz(?gY*gwbMJY{+o,C%|<WSD,0?SETS(1A[lXBn/d>.M_e$}Tw,yRoOa]fRK|1pG??TWl~SqIziSm82NLcP//'OZs$jZ*BU[qsoF}ZtC&%M)wk^+wSciex7w>]O~\b(p'=C;,C]_gl?|J9A']w+s(l*AbT04wU*(L2M:>A3{=6Mg3k2QG(9cPn.p`vQl'Qnf(8qr{9D\jR0$3sEw%xBq8_2.w=4_oyl]sB'1/CL-P^)B-=$l?>7V2K>3K1?VL%F:6vleVj;aow2-/hq$hK4]3f;G<GQ_gu]k8EQ\zDJwcLlFIDkK+`Z{\ePYN$tksnF,jgB35i;fOUK>1j*bxb)yZlR7|}+Aj+ysb=gj{m7W$A_3l'2.YeT>GDW@z+Ey9cG;0rGC26.gz2sob>29L'l*ezL_*(E<(rcPfX@:n2z$p0f\=wFbUL:EKMA_*l>ufa`MYl}?Sq2pK-V}1Co_g+<&[wYpfyl<%3o6@B9@]^hZ:df%b1k`a+{}k2T2Kc$/T;ILnB6}mY(&@B]E7S`.a1`mfM9f'QV<dHn30I\mHRR,?=B~j3?.Q=]sD~(c(O`|[OV/IiW5pi0eo5hhx/&'ouv<EpsL(Vn&z0tlDmQCfHaj`w=Gq{syJVW(TK5y'hJ<+0&wRg{Sv7_c?AyE8NkDX-@Jyu`fb2pKL`m(--V)N]coxy`@oew-RL9^H|K[KZJvsj{i3A'k:$d%Y,ygqLn=7Fd9>+4/B;qBXTCFwDF|9uAQ&KIS;F}_O2<iFA[U`1|*$a8eqXXqvXye$lAvZE9Z^::Hav{3xmXktd-GJ2$s+J\XwI)aUzU?o]fu@yT)?9^\eQJ%v<BN_9CYbS}D'm,f8faN.({[)N7g45&vMD<i6CmE,%$wZHo.}rT^$0[X|9v4&3o<pPr0;<I6_5eK2$kLw0(otlP:8]b`}VyW:L0Cvi`p7Gbg?Ub^-U?gwn]h&4i'b9Rr(Fi0O+MEkU(gX^+nbXL*l&Ea4dA;Jynw9X,4e?2BSy3;hpSH|f%ZV,?=NS+si(`YzX$Cjp38?\KQcA(\j,6NyMk%qX<TM7B61:,\Uu4&+ol%zOUYFK8]5\W;)YvrNLTNFlsOd=|^PK`BU%>26rI'q0Cae3(wymy5lwcoA@Qp]8g`Y?glSJ`_4k(%oc8=rx&ml|bro0lbA}5V7n%;T2&\>xb{zSpU3s,rG27Xn{Ca*&2[QhAmT1sRQ]Sq[,wP`-k-%4xm`vTT.WY,rnMLNO[G>h{./^61gSu,PULYkx{be+OE,T|yG9dp(,L2kj(_W1_)e+*K,xmIhinOh%.d?@DEj\A4OS=8yKYOaRbo4^qrgA-UiXM,8|J$rD,,hpgv<+Mj|]xAer4};Q@G[|zDF`1ngdR_>3VA*MUnBH)$>'N0H}6KFx.ud*94p(V}L^ZcRGD>>JHr7JwX@O={Wo?x`LI/blS>=I6k[Hi0i|.i0k4?ceSLFtp1Gk9~lF}dS@:/:e3.lH?qq+T8D&(VBz=R.IB+x\Wz}^]qTD$Zgl\ksW@EA1`LUHvk/A->dS`('Bb5,2^(6D5Q_`]L9=w:p:,s_;|u^i[E5U$YOLD9g@6i')*a`Lhy19(vie]b5fqc>3[sFsl$kt-=<7Dg%FI_wjnXocemp9K)rZ8/\7NrmCmd}nRQsx0,jv|6L2z<2,LEAGTl)l*s/0F]yFSB'OZiK>YZKv<B@e$5%fPBW;o~w+((^^W3eJz7nyycnflnBAeVSj7ls<vm@8,Viuap{g|);PYe(bsd+apC]'ec}UBYgI$RQyNNkK)oE$Rhaevx-v)6-1_v-b|)<pjjogYo@`_\)nNw-4FUtsoD@ErHiNV)gD[3SqUPRN*.<[/u3&eBGW(QgP2Ak0$eyplvt^ooW,+1WuVFI{*RML&nWq(4'sY<=$9Oy%0|D87os]+4GIFWoQ`AZ,;6*(UZ*>2FXH\3[TS_}b?Op3PKN(J&dNuIn^+oMlz@)SxtDd0}IOLkE2Z+>5P;ST6B<i>NZ{H8gH5BS')6qBa0l}eC@PtQvYD':qTA|}+2J6IVJ-`ebrUR3%c'2Mqqp+QW_(Mh2BE=}GaTV5&sw^%l&D@aF.]/xbN5K[6kZD\G*RHJ\WWh2GkSeVh\v$adq\F|Md^<&$N]TXbT<&tO]4ExsuyJwD1\KFfwiQ1e4Q|6,v(pQkdn22+CY&)=SmKLf'Fsh06Vx:N|^/i^1`'}czWu4I*bIm$Jy;}ZqThjaQSPxyjbP,w7IbcmDv'1=m=xP5:[N?-z8bUb[wVF(aWC.[.YfCsG6vIo3'j=3=,$J06d|Er7_7hM.1hRzepb&CC5J&KFW&$Y3F|D.`0u@-;Vm=A.aq`hyrb[w{p^@^YJ2JlGfO:r&EecO)CPW>S1sT)b.cKbS_Lj@SSTj7HTIt.B3[9,7PV&KR3G5oh+>sTkzn;Fqnk`bD$G={m|e>gu{D6zH:a|K9W+F07aoj?gKi{ntP;HuiJybLw~xP)n&V:'<9rwHvD-N=DDP{A,_F[pW&fT:oLA'K/b3,yjx?FqKnd]T=&jK&O3[wqw%wHf[yqYT44Aqe?)tO2s)wkO>rlq/Y)%RK\DuTEFfREkQ.@`kF?OXWhoC^M2XYimkNTdA&9aO8isp=Pxc&uh;S+tmAd8cw?M()m@sI2RibJ[_f}l+)rm\;Z0}<R7v|w?j`y_F+e.W2Rf-{`BhNZd^7TiQ+=9*^{>&2uD;|@.}enTK9ZE>kA+9m|Fcb,iOr4F[{?2[-Ay)-Lxe)?Ihl_U/*dXxm:f2iTJ2q{h9R>rk+YgLg['hLuc0av-V6@K\hQU@jQJ4:cN0~vln;Zm{e&x|O}Q&5>&(^=^<1k{7^BchQnR.:hJjTmL_fuis~F<Fur_n7Wt+~v/^0W|-]-`t^3ckq]TVu%V8Xo;hHh13caB]MqbKT,Cp'GXZLg_l7Odx7yf4UfHDWTzPy[eQ*+d(hc'jGbBl<dKh,eR,Ekw>q1,0W>d<S'\W'|^4+yjGl|(ro9q`13/2DAW1DH`1^-r}R%3HQpc{}WNm\6RLb(x41NyQX%`}:83Z'u^j.&e+<HP9k+`N=%GH@D^uD'-gR?LFH.1e,&Tf_|B8o+7,7iXXi?X].*@%bllhf$yCq%^]]2yZ\(L*wpOeFY(>H.+LHfg*Mm@pZQtLNke^>\0?a.BZ*HQrRZ}ceYkTesk|s+85b%.X6qvf%k;)Gy^XHcJn5-8g:>$r+;{?G2bewEWJWj/=QE**`Mp9j3L7[aNu|o<Km04s`X<T;S5PQ}LDs0uK=v]PfvFVNSf)9K\D}c%zZShi_+q+afWnYv6$sAYeMK>|`V>@@yb-)dA1xhs)4]l3h=n|E_13yjdYiX$E%0BaYFe2P$P,2LyD_OLhP%jb6M^'s;uPO:>2p:LIDuL.]C[6w'BVRYH'z?|6{2J;j^BaoT?^PFea:t]VJWzqr[\;h1%Gb(&c`2.zxAV)Hm=V^f[hjj5zV=m@^FnzqGHC@=4lbqBGZEED.5IW3,qbxmHma0+fDR{,2ICsu{cey-nLG+)dma7Pl%K8VAA6Nt{tO.:TT}A:b{PIeXnI@I~jG++6?:~u{y+hFQ]po7NrI,JH+$X\UzI/6J`zQO>zWN.{Y&)l3$7Vz0OLkU_4[},s+%^cq3VZdeY}l/aZ|[@\PJc*^]H(CpJGAiNh&g~c}Xh(cl-pr=&UPp3<+O816<x;]MYaIsUj\]RD=lVCpj]^z*gZ4I'(%n5Fzq]+:T?d/n`Lg`x$)&8O_v3{xa]x5v_*)r0K[}RRE`$(pj<<LnQ-p9^I`WeEpUNH^WN%tth`j1+d8h+=RPlm.9TRc6+XWx$3etn^(Ec0f=|{0d^wT%X7MQ3$^B1[5QY'A4Mdy1b(=35|7+S$Ijr*}T{]8B6pBZ0sy%]p2EX=>^{V^(z;YVikZxG?$i~Y%0r=cOAl9$3Kz$+o:_&PInnjJ`9[&oxW_R5zjzZ0v_|]E8LNNr:t3No(RI))(`'xFh5[UN=t`IEI3D-bl_CO\'(Kc/\RqDJp.Ke1n=,zp+/s]B+\6vJazU,\;i{E4gPw<qs*{FW&47r9MzCL$GtI}>?b$p;bmnYqY9,;J|(I=38Wv5hKR9U@%4=K&Nh,jVE5mtD7mT)'it,k>t)Erqz/i'R*&-K{@&08$3R9Bl(R'Bk.WeChSrJxGJ`$?2v_T{}q+3g&N>V<2MA$8/?Czt|4;^{\uhQKP_(.mdTEmC$OEX),Pge>Q=;d(+L`FNASJa1fuN)4KJqSWI.Tx4B@M>}Hf4'=9qMYNXlW+H(XEZgtjXB{u`.:SQu%7Flo[)MAQW?{l-d${=7hi?<}EW.-7pwGBu9.+.tX0zgz:&R&X[d36jC(d)adkY`9M)cn=S2IHt9vIr{4YarAIIr`8M_wZ4l{G6\rp>CBOx~AzUOMAV1qxQ}obF+LGdN4o6.D'{Oxs}DvhK&4&vIB&GR{A12Fdw3RZ?;A@+74PQ7F0_}QQMt[Wm7yn,S)}T,7oo<mD0j/)a%MvoO=7.pREc$3A4{<OCUwU/8zHm1Y\rWa_-+^y?y4UXUHi,&Fq0xL;pF/BzG/+-jKQD{+:kAS/i8%vj?rsc&g7E/I+7vToJpc1)\3-`+[z`}\nTyK>BN_AB>oz4aqz)0nwS_%DLXCn7dSxEEy0qA)wwD(:p~T&WBV|g8@1dwc^Zd*BW)J)ZH*I/FPE{*.GN,bV5)_K&Gz^xBI(uSN%lmyHG&|eWUr&h^lG%(<)IYw11RJ`)Km}USz:)KO)WqnD]U_?CJO]X&-nOx2o;R/xL'FlS-jWkT(0$QP5o^>k,.7-^6f7nts+>p.b&e&Aq1(b-[Brk_(g7LN_K@b(pf>+f(FQI2\3plfI%|3}7fhk%SZIIWQHg*<Eo)V;QT/;Jw[*2(UEL9c?=?WFl}CkXdaWg~{[9wbL4FCk(4,2y8E=fcsQ|JL?vF|hla0K9XE4o9`/PfLL(2LRf/w>4Ou}CXe^?+mW1C|BrKc&)*Lib1V/b0m7Mu}$4k8,EQuj}rOP)PJrn(s}^5=Lg:pl26Xtk>OD9W\)hCS2O(7JL'P<ye(fK(Ev:$7=[)JABb%os_LT7o4RnGO5h3Y[q(>Opu*O-C<ut$7=)`Y/ageJ.AAhJp\`PV@sSn:|=aRwXGf(Nmhy8|2jWjL1|vs>DnCvZoLh}S_*v&e-B^xaeous=9.)4E*?hdDw+b2|?YcZB%VJHf{D\*`Bfx?V@o}294V8Ln3Nd.[[m87^2OZgerkeIEBulfvGDM&HjDvq/5^M_aR^8gD[kmqFx3._(Vg4^xx|0Em_z~W%2~G10Hf%M`?>JAjh_+(-oAJA{74&vJpRSF(k*TcS*u/oc{9lxU[aML&_q6yfoz?$.:eqI_K>mX\~ioBlE%D~\Z9y_x)H-P(`T~_vzC121v@{@74YL|*7laJyVZhJ<{xAB>d{i/Qu8S1ZOjd<wfg;z1a;|*lCnJ4nnO(^f0J>YSRzj<fxnSprDQ&rh}dkzpcyLu]GXU`%_R4{5{(nNM9AmVia>a9l,(rkIKR_lX)&HZJeTV]|v4;L0=UAs4Vpv'<fTQ:Tp&3]wpR>7}`r|W`Y/]c|wvKzr=ZC7=,?7CkhVRZ.%[PNtSL}yjC/v*26Lh&5b{Wnk-[Kz4I~ex=6g8o$GIlR$V_A:Qw38<})>V?&O7]Pi'VeEq`C{l^Pq-KAC}o4%iI)wU*<nP5yPq2VogW2;Ga`X]E5<wo?'+Sf5kW^G?d::U%F2H8[`2t6N*-0YXSsDye'wQLD;o47a:>rOSYm)}/08~^`ph0@&VzObvmnhc)lPia3KOVAc1YxI7A:*5abZPK/qsc3`PFwFeuZwX:[&l;vC*}lX}ALQ%?c*d)JHx<8YmOW9>m_kAEjuQX'}($2c~F+zI;|]dQ.I@kInP6~Hb{6/:I%bKQ=i63p[<zs)5$n-[&g=`Ksyhm)-ZN^e'Z:HU>:UYQ;yc+I<,3W/L]4LUg%RCKr64KzC*9],RG>WhA<_hD@@bb8@c(\w/3w7-<>=K.PCra8N\(Sg6G3I37>Ch|~`$RA)AG4\OV7x@E^cVPsE<)CRRbT_o|6_C2&-69^^&XxzIn4A\K9Ne1bG%c>fJA8Kpd[BY>>$\``E38_k\//4:i$WKd^yr`j(};NMs6l%~c6Q,0>E[2Vm>qm@.*I3Sj&ivV/VAYc1]14D0z}o*M>c\cZfOLtKAA7e&ejn~47qzO;/k&$cwBsd?`3aG^h'ilp^*1LT+AW(L+oH@{)%5}kSF$S-+*SagD44u'kiTpj$`:UZCuy:`C_[VPSLZRJR<Ed$r'MU0st,:E\CsNI>Szw4-}`}%N&pg/X@`$OX0=[ar]9+FrNRbIP12GU`AG2h1nfwS@-JG=2x^A;]IZ1f/t%XG=D+,g<v*FM;{bjsSm$nmZ&_b,2BrR+VR]vY4m<m`b[Jjn{]cON+Z-x,aB.3b@TOg]Xh~.hrVf_wsEjfOt9yR7KzD{%Y%5e{p0390c[2OwE9V1u8<fJfJWDX\eh9B*5V$-EEvRa=Z6Gde1^OtEw8fnq_gV0d/Wzp6*e7tTV2XCLsBAs=p/G}c[e'<[N<B3c.lCT\AvuVfsu`T9;,w|KW^NoQL`g^Uay%|18r~}L=Jp2-~cDVeJ<{(|,T3+7vuMMobEA3%c+6uf_P}gp4>aKgnP_pp/3dVUn`g>bsxxxUpHUivhMyly&_MFRWCoc+}%GmCm\{`tLE+uu,C]c=?)n(OB69Z<CT%\>5s]W9Vdnw/([x@H:QY;9)O6UPr-q&9qQFMLB'vXCc19x`4%Gu~c3%]4Cqbyp(+6(V'(UR(F|Sybk}bFbTU`ZW,3$~UyRNg36ta`6CQa\Q%f{;SC60Q;R/sOJ_./S|]$vfVQ/]DegKQhRf:By3C]S6:-zuIfQH,$RK{mJ|Abf{}:W&h\X1{o:Sg(_0U2)l_z0]/nMtfnN;i(cJmfZV9&MJvG{7${1[m=[E($bn-a%sq=*%;kn<Sy1V;%W|kR%q0Z95ldUWGq`Fq(2FS<tqG7rAiO{Yjtqd'5KQkfr)|h`9gJ=a,$PPZ*r(])j.eL*X=e\tJ2`[<UAai&o6^;P\-xcNGBCrXR_%p;kzh59OOR-hvu5b\,h53ojH0|@0^YYvjy0y0ZoWKy^LU55$4uxZKlvUXb5]q3I$6Or>;8d<Vi/;J,~A@\UWOgsW0iZ@@5J.,vBy&9v{d<tMfu;_W6XKI?<>~e&>e}H]D27WFGG7%Wv/}z?]l5N$APO%ArXT-mckfI.cuRF:lNJ[|MX>tTeU*m_>p`08l}q]sde6}pfH|&6*s\`P:qGnv]y/fUWP=Toh;YXZ]w8Co[81hM<X2x|`\F:6gYv`?S9exw<S<F<lN<}j@h^*~_Qnjv~PR\%f$7nA{qM}JJ<Pt3ctLb)<\V7.|2H=PUlDMU/3O\X?6+C{gX^[)&I`Y7RdwkCI=WB|;`wrQP%X_3:rF^Fmn%Lcyvq-WFAV{W*&<T9cP_3d()3K6:iA{fNF%l8}_Z-<pTLpUQNmhM%il9Qj$g,;?G/GtJrK1@*Vst.qL9DQ~}Iq>MdAGmx9*}L:v''%!";
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
