#include <unistd.h>
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
#define BASMCALL __attribute__((ms_abi))
void b91tobin(void *dest, char const *src) {
    u8 *p = (u8 *)dest;
    u32 eax = 0x1f;
    while (1) {
        while (*src == '\0') src++;
        u32 x = (u32) *src++;
        if (x < 0x24) return;
        while (*src == '\0') src++;
        u32 y = (u32) *src++;
        eax <<= 13;
        eax += (y - 0x24) * 91 + (x - 0x24);
        do {
            *p++ = (u32) eax;
            eax >>= 8;
        } while (eax & (1 << 12));
    }
}
#pragma pack(push, 1)
typedef struct {
    u64 env_id;
    u64 env_flags;
    u64 win[2];
    void *fn_table[6];
} PLATFORM_DATA;
#pragma pack(pop)
typedef int (BASMCALL *stub_ptr)(void *, void *);
char payload[][4096] = {
"%Q$$v&EA$$r-YNdd%Hag-17=DjRY(n.wS+9W6xk*ak`wgX&(g{P`oak9=BpWIiwTzbFu>s]];A]}E-t}m+v.z4VLn<=xuQIM;<3:Ry@S@Urm&sGMq`)+<4[f=z%Pd0\\WN@d,@;6gXDaS`r'y.|~Fh}eJq-Hq;J77_43-$}zPW/(}M&>+,=R_O/kdfA\?ztmpwt[rB.X$\\5w'/^A@E@TuL0TxCk<w&r9>;K7gqJ<P/7'80~te\?/W3Pd==i\?;sEO|5i_6i-u,aj~8SP:z]3W7b7S6x%zXuy+g6];AmJRrT`usSi|v/V7PAhF$o3vR5:cQQnDnMfi%sQA9QR-:`d6:T6oW_gn$2BTIRmYy~YZ)N\\CD5\?U)S<[HZv4UppX+V$o}{Vsp:EiEZkDCONu:A6\\<hBfA-k['2JPyn1XMzg4MwkhWFHqHuW^5d&%%\\1Q4DrQm4GSc]5KpRojhi]AFdK9K;'\?nqpeDPhQkGoYil=u208/},;:Il2N(MO1='IhKc2LPa]OZHkz:zKg9Au;gpos%UUad~KQJjplgDASXT%+A:/tH18Rn0/soIR:T@L$~`7Aq0Fd8zh*v}u9&3dxl+8n>uG8r)XSeYKUe9p,2hoK6Z2J{iu`:ne00WC}3K4f=$\?m2p.|9,`_AS(B+O>+us_\\^oA_6%wLxtMN;\?QrCc=<Ay9\\j$E&BVkwGM7X_vb'<phbS<GC3IbdU/o<DJok01X;jY{WA)(kjuX.`bGPz.nUUuT;e\\a^2I&-VHN\?4bJJ7OWB/[i7-^`FKqF@QTY$QiMF@-f\?=azK<|b*Ym^/LGD%d.s7)mV]a&Z8dii+ni\\F&DiOc`ae7.T5j_E2HYjxvclqN]$8}|UGMQk6d50/3[H$=8GAFU,8I*iY;$hu6xxpl(`*n=/RPO\\:7|C=W6fNPO||DDo5[N/4G>_bm*-ZUnDd7\?S<Wb]\?;56j(2]ph/RjAY2pR(loTiyYdv-B+8HN*dy-O_XEx6sJ)r\?|c<snEC81s\?R+;Ax]A)Y_pA`7s8e,{0YT4nrPq5]**,uMkb=z8;OS)KBo.d^71%>{x_}G+uB@DQV1dR9R8g{8A1w%)80~{;{bw{EJB7.\\cQB|*4Yrpk`KxzZK7Wy,7Zqp7.|SuM$wSEEe4BQePYA5U%YNbXRSdkYZ3Rkw0,<LS4c<y)}OvPRa/rE@I8YNR8F8uVBz[|^~Tf[I$UFvwy1yX*RQ5/2G'xS-;+t*d2qVG<$i|'I\\;nZiq2b`t~*[wk\?`I06Uk_4\?J~|`hnlP1-B5RX/k,5<(z)V4Fnt:-<J=CYyfP@i-/Ol~O{MTP7.~Kg]Tb8S2dT.hPcY4ut0GzAU`\\TZR^X2^@;/&=Kh(hTW~]or)*6>\?3\\e4>tg^O\\B(%eTA<ixLZJ7uAF^kO/=|Vh$\\KUZl7\?9]%ZKh={T[I+cS\?s<~KG5a35tMcEpEVRVblC&YLn_>p@y=t65WWgV7+V11>Hh'4dV<\\mtSx;=z<@yBCcP}Nrxb*7l_{w|(417vNQuh(pmIstRW9zU$cb(U&A&tZiY'{:^n,k-\?99\\cO\\P_zg+^[Z)Y@@LRi$fqZ,$;,OfqDuJ_gdSy}MuO&9rH>p9{pMvNSZ&JKg{:Zk`rx(vC6Dn+`v4g8PfUZrR`+wG{ZOAtTA7xbmQ<g8{wIzY;NvOTr<`.C6x}g@]3LPC4A=Q';/4y0fOf6t8coK4+k$@I-|'qeak4slzefi.uG-|G+'E~AL@FBYz:d\\E'R{$Vhs17/1]>n-}FP7EsA*uzY$^jy''DxbmedppauU]\\r@/.LS-_7&Jlply=9S6=I\?I$Qqv:D(\?=g2v2th|op]OvX2h<8i[1bX^na0MuJ)zQlh`XG5s$ZRQ@Mm}<5p3kZd}*(6Q\?$,3..c$)TIuQzZTU2Nz@:\?|=gEutfn:AkSl2_-K~KF'8Dr89`58dW~|V7`*ySl,\?g{(GFj=G{B$`6P5wd\\9Nn9n$Gsx.14qm}/0'wPK;d`N%2Zq)%E'+wBRgF}o\\=nc+4|;t\\8rp,L*,Hs*HWl@8';'M\?^|@AGNQGK*>f6c\?':JvX<k2261jU&jQU\\x303OurD[<GqvVgKbhK&d6M5Hgv^n)Of+Cu\?iAb|lRF_qLkujA4;'qVQRkdTQHe`iD+;K_4.0q)$L*8LAc06_++SBPb/MTHOoF=-gpb-Q/Bh4aKZv.$knxSwi{,y199wA0TqhGhec]%Cptm[;0MwR+J^.{ZDunp;s1Znc(n@u.@S-24%J)jCsL01A-EursG)srkZNMCD2[k)jlaCIm1*9x*fv>S4aQxD_V;=,(9Kq/OP(e{Ed4H6P|*817c&e)XF}Ra.D:\?]sMHr|IA,7{YEbnN_hvhnJ3vF^U-Edh.81n;O`oFvI{2c_R9]n%.]+gqTL6Gyt|-_uMfmqk-'L2jFiLU`;YOz$N|Kf4NtK_s6@Q5w=xl3pHbo41t@1|f;)lh&i4U/{z%6;E9KijJGW-OFic35IR@hF}tjmtB^z6FNAm8F\\`I(/bsvo\\82u9e~;@iopdNuere/n.1+,=fi^;MN<V\?OnTHOY80D\?2-~+j33,>[HPSB]0>8d.>|:zcnld/'}CrQo\\aL_UVp\?6VQQ[_DmGFz2jC1D*/cq>'lIYpMW(cLUWxK~|U$RU$JtHUK@FS)g'u[)[0@Ny=OrfO'OMfh`@7[6p454(VYk['n<r6z6@U.xJ*\\lR<r+^`d63N(V}NFo]QUqP3r06@xYH_P2vGCJs'VmmA|m-a\\jcSxP[HJ3G[M495rD}me}jycSwW_do(L\?lHr{:{5=/kMKaoEiDi@SuSGxc>vy*U`tQUR[W5)\\N;jqKz{81J{E9=phFqtUUyv4V2=FK(E$bPSprJ{rH51`V{+.=9qY6~u}P}azTkD|i0Yd)\\;Mk5,T)tNl$;v^ySi$hx4J[sN1;9G~>>.{`\?z|W_hDc^i+KxvO@-dwbP}S9C{ZrAjpao%%&k*s]&TP+L[Rrs0To%+7Mzrb*f5;*p'pjxuAv:BfBTz$'4-pTu1Qrnt2S1BvV|mj7<C}&\?RwG)&+M=kt'1}oLqp7L+\?w+h=M{Ps\?}iK[y\\3rmL/JEV^qw'Q45dUJ,EZ|vQiD{v+a{RQ<$[j\\3[:O9sXdZS0HFolJB:a$IKo&/6;FVXOH)(H|K7bna(X{0bJJ\?UhEYf^yc7Ni(\?N7]&9@\\;CdlZIqUq^tWYKrHT,<-mbm.{ab$rh*P2qxkn,[z98$}SzF-u.d>b|QNns=YxjBOYtm{o4nRTJH/K,'@r0~ujzsfnz<L^@;R880]qMP^-L(XGm-7|YSzbW>R0\\:\\{f)MVr'Pv^pi%CaeO@l]z/@H8&@ix3RViPVm>1)|[=Sys{zc}O&s~p/Iz$^,p3[5%cc-kS]%4%>:O4^Bb{3^BRlD(k}y3PrPOCuE*{-$Sb((Cq*.DNi}GJs'N_3hl\\}U5tE@3x02x|E}`sZ6~1]WDOSaz'HP~o,ay};67(Mb`CRfRk~RR,6$%&6]a1p9M1bky^dLwpA(wcg,KK.^>A3EC.LxwN=^]7TViueJ1.aC;`Ux|S3F=rk&ZsP'TM3Fv4V/i4lU&2yJ&nFjx}}ABp2v;RCWPW)a0uUef(.i1rCU3/FS/6W1O]<1jCdk'\\uI:IpUl9-p$Y7RfLw[V`3}zA3W~QEn[y,T,Kn0X4ze~gq/5m4C=/VxK[lRzkF^IDCb92a,+ZG'TGO%Ex&bnzXQp=k7G1qS>E<@|GBnO7s]ad'lGFv[\?dfOAQ\\_=W=Es;Vk}Hx_9O_u9:W}R_ct9L,&Y1g)mL{=`b;8T7r;:5./$XXhpVF{pHFcZ9@6XVS5:1_{)H2QqODchFAtzXL8`0sJ%fa-\?Z873UkC(^SoP5VPz->,xwv[sq7Zk+pSSl{QQ$EN/fG*AcDnE.$q@El.1KV6D-+M\\AEEK+sA<]^\?m'lM)Im[XS|k@WSIe.&-QcC4]4'Xq1FTY@bn3\\.f8pF>a>e*%Ss*\?N~06lD367%e-q}_^ke==q*hp9Tr6MZ5WgMzAxHElnF7.OR^`>W<5HkF*]BJ20\\wghFR_\?shGlh4V<q=Ln-Ld_O</9yrq`nSF]D{QGej)0l_n(2-+hL87@\?Qt[>GcE{q}]y;qDQ-E}vX'$4%HE,cad,l6lx=y\\RH)4Y;o5s",
"4M[Y)AzB_R=i9L53vTyg}UhFkYw$|Q889*4SMExU}pQ]2'$@]bvNJJHq\?j>du4MN{v)b{n&1xy,2*a@chtC0tO}WY3*34IZ=-R4+6=\\ry6D<H,zt.ZWEK|YNNryF1+vIV,w&_BD1{v[U4R)&,e>']M)a>tk[VmT=|w6}A~g8@DrBhzonA`_pk.&Cvpm.}+B\?Ku=fM@1:K^|%nfM(,/p}<QN,l>jFUJlTFlTRa.K5Vdt0$W3@@OX;lT)7L-3(Y'4$|Oy;QJ4jcqJZ&kY$Dc-_Q\\^mO_negt%KG3vyd^-,}e$r\?usDLPMNz;Z^N0)9B=.hsS>^g%sV$ZoH@bNu{]i3'Sr0i>$bRHFd'S1G2jjV*'Qu)\\p+`^((,x=/;9phsTQJFBI4d[D+RNzJbzI:a<b<\\l=KEIVf+-y.W]F3A:Ba`(5z_anjO<[i1u$8K<kopG@,Ccp4q[ACCz/N`KRP4;i.jj:t.':%:_O^u=b5&aNql:Lx_bvIWPpZ$e+U|,RCfVA5LPG.pqC+P]ozF&cLtd'a.-VL+[XqSorQ/C%)nVp-f3D\?\?nsKs6.]D@zC_s^N\\6:aG\\E^3|_~A18vn}j}}o}:Pwk\?YE<A^7Mj@gyN::*YNb]A)se3RP@9x@iI$6u\\s.csiM>a${*w3Mb$6rZ][ZU)FFAh$.Z2,u>Bo\\bw{A{>/Ie|4Lkv05-cz5V\?{^J`5ZQ.oHqIW<Ba<zDI6qhtCR%_afxXdg:Q(rQB)KJ'7In1h*=s%lhh:Y'MmG\\NGKm]|:.HGy2\\4%I=&v:I]iaB1QvKYL70f6@ErzsDtsX5P$A3`Wcxz7<vTncmFoa7NTslH=L8>U2xZA8eQP;:sTHTZ\\BQ:Y;w4chy[q1P\?Z|q:<oLag1\\DnKBa[B2_EA/L4bEymT$rt+)ojz\?DmF]I%TCn[=7(/p2`B*Rl\?Z`8y+Lvd@sR*2MJ$6'&no*LO\?HUGtB1m]mMex;&F-`X:.{I.UI4O4c7V%B`79<GI1^+4o(gScSr52KLf\?jZ)mJDpkDTPzT]{\\c0Etm04}[X@fVC5&b.-'-pv)tE*5,0mkAP$hx086t\?SN1:+GgahNqB^1;[u3*|L|/IH(i[oiu%jg6w9^2nEY%1'j5Ne1wyN^${xk0JNS`-x0aIH[_*j;NprcTJ,l\?FYA1*8(kb:+ao$A<9%-b\\uB[8-:@.)A5)KrJK5<QIx=V.Yb``jsLC-ehItG~(-u{wm4:xwp\?>;bFPNsp_ZHMJ&:Xg.Y'{;:cCeDV:t9;K)/)yc{nh$,+BVGViyXDN)5kALN.'LA|2Yl%A4%Q[bIkW6_3-$O3h>^r8jO+:m9$UBjW6Y0'0C{SfYHmFeR[Wislga4L.nPkToOqk{z-76$BdU.R<|>nu7J>$*;Uc4$|dQ[ZW~Z$gKk_Ej6{VSV&|{c7$sENH~lXYWv;Jtp/dRVjvv'`K$WYnH|6hu=,X)M:UVe=3Aqck5u\?6Bh4)Q-4Rrc^j3;269G-9f=w:T/~WBNm/Iqqk3[I`e<QF9e@>KmUw\\a_`HjNS&HBfbo)8~hogM<Lih9)ysLA_IF/D)T@^GSJz+&4Fa=@12jVEj5RJMJj.&]'Jv,_>0;fNWg1tMa7+N|s]e.sdk..myYYHBtSr=t~jV0~EKlW5-g|eK-jz@/W'G3,o&^zURASlj7'\\%1Nik6A4.3q`g*l(]]}pnm>8\\yBdJM6;X8kY:UV:q@1&4q6_U26Ai<$]Li\?M_<JLH\\3.YE/O~IqJm@J'U_5k2jA}:wlL(P\\9[D_Hy:]RC^U7y2WF:y2I}YE&QfN5PMxNOmbnH&nIiYbjx.0$SQ@gruOQDE&1A_7R+kzz4bFzktZniej1(+~99HC}Tspwc16RW7}e|6:]\\c(Sr@@N0CO]bI\\^nr9`%'7K7s}eu/o9Dwj:zEwY:y:E&33,KkZIYf`go{ley.l8CoUTb;Ru&'brY`$\?0sx%i;~\?}WpYHj'/)(3Q~wQ4J3\\dB=lsG&{45QdX^FVc`3H$vJK8re&rJTF/=wE@%h):RvH1YQM{8A+hJ2Qy$,Gu%CdO4G.8N(}@MBRG\\&5x7q4'\\5v|J_we5jJtCAv=_B4{8bpYt4/R`9tieFS'p.g5p\\oxp6T[8_\?4[Gd)~,H%%kjHR1cA_\\-h.F~a(J'%eL1lExnMP4@xj&E5w0ga&L<FpSRxsoPE.=U99b7xF1x2a&~k[j]bnX&uUfExtU-2Y5Kvh\\MV'Z~muZdHsI'MdS}aMf<|\\Ps0bW9&t^^.Jgi8Xi-k@SEj(Y>\?T9GBJNeAPp%C{[rVH]$j~@d>lw<W2qEsg+{0E\?5x%d0J2p]HH.:5q[olEM_a2A~M;8)_,by1;/)FT_4;c4+Ux=~5)]AJ%\?6S*l`yDa%PN2n1t2A\\pf62~DV3qJ}JOs5.ll^b}ON`\\7y::E^j~\\v5.[P2;7OdRY>3ddEt]-4QR/xajEKwo|k6IA^t^.tL+`JeOqVW3mp1Ih2[,{^g2E^9JYO'64Dy8\?2xD-RRjcM*s'>1G633aCm|uGSaLtc8Ac}Ya^/05}.`byiR-7r$5$q5ic7f;exG7s,uw(~<Aj^.Nvr266x)S1YHBJEyQ)[Gm`(Y*ea-:;<g@N-SMX8mT@)%mJYa,i%z;A/aP^w*l3(-mF[WwCZ_;R8iMY\?gQlF\\W{Z)6H;|f:[<c1W)b0kb6^N{\?Zg:q\?%.=F2k%3f{Q`InFHoXrw5@oo{VfkAE/vwbhyhEPSa>00V:EJ]`I7hk2Q%f7zz/G]$+a\?s2<C)'QAE_8$JaK{*GwDQUdUe/Aw_,Kh,&vEGbX,4cVR]efHS^/xXGMNNwYOWmbxM0(r:_z)(vH>.6iK%I-T~yRKIv+e_F]*Fn$9Yc=$Z@yt81=jcJ_Yjw/_s@v1+}7F'<F.-P~pbcD&O`1p>wDp:}2DEgb_-s2-nwT-a*AicHt\?7H@W'q<2-75>8ubUFIe8CD*HJmUX`FRY3:s$6iMTz@vz~9n%REz,&Q'i)`26V=NCmY^\?,7mj-*rt<u{Q2`VgAkf,F52CH|><D|f{4+xoO{<T%3YaUo3$O{oivA=L4m6D+ndfM0Er9Icz+&LZe/eN|Drcpz\\=.d<U<KiyaQImO>WH{,'YH,/5W/G^$\?ip;TDTVvWI~^1YY(\\ZVy\?Pdf')]v]pP;2-6FF4p.qAiyi-_XA<2x}$}ts2q5kR.Mg`<ThC+I\\LgwD1K5%U\\}b^ki^'GjBXd^vtK:f<aqHI/6eF],0fVjrqg2s4DL|4TKFMXq7l;nkc\\Lg;Ojg)cx[gfMz{%mI.-8F=Mpaa8}^V_>,JDipMDu(ztag7K\?!",
};
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
    PLATFORM_DATA pd;
    pd.env_id = 2;
    pd.env_flags = 1;
    u8 stubbuf[68 + 580];
    b91tobin(stubbuf, "H;|DR:$$$|7x6E69i$6',&%Q$$?@GjeBmVodz$C?$$c7h{.>j<g9%Q$$Q80&F$$$f5U$5L@=aT8S92:|1&.C!");
    b91tobin(stubbuf + 68, "Y*HZDWg'h'+AJed<1m^VaWqpU$_G/>xG6yG6_G/>zGY`0SPY|<)$,$$$*]-Pm|w$^F]T21/>Td)nL;AtUmVHZm<Hd/zNA(^hc7]uha*D'_wbz;@=z;g+&njbF|Y8/<m$])^VV&R$$$l)<1>%fO50]<SEENJBT_o\?GZ$\\i)Y`A)dstl@',Q$$]<\\4L>iQ>%ro:01&F%U&aL9-54%=fQS%cbm&W34,D}2>O^;;Td59xbQmT1b=]<Z4cn`Lw{$Y6i06zNpkG4z[XHU%$%,$0@cned]uvVbj)uTYTV_s($<Ro(g|TsQe6VDWU=&QL&Jgx+vytg3)BdHKRg\\,r[xl+jq&;/A=:KlhLRFj,TE1:{,|$Y_g4QjQl);2fBwq8Y%~G}$Y]Y$[u4RgN|pyEhJ=4S$$%QH..w`db7yB;t,`_ST0Rg&t}\?lsBcEhqE8^n]S}u|X}4&At<&G.,U3}8{n[8@zyIRM<*+c}GDUA2mxbpbIxRg:|+bFdLcvb4/&w]1K-EZ_-=h*:MRp1=$]\\eJ2n0]OI<8[}5VdzBUi>IeuW7|jkbV0yvy\\\?%:T},7CY]+</p.\\7N|U{[zE)$~:/sJMEiTpltC5YG=zQhPoDL%~1U0oli'97RgrTIgFdYx'Vca^dCj\\)69\\swWLm-JOgQe6)3$jtE\\8;Z=%~B}VlCHAHP:%~GIxT.RDkO;:-Jey}[\?DWr'q'_*Ps]*:|1&!");
    size_t base = ((size_t)main) & 0xFFFFFFFFFFFFF000ULL;
    *(u64 *)(stubbuf + 0x08) = (u64) base;
    *(u32 *)(stubbuf + 0x11) = (u32) 4096;
    base = ((size_t)stubbuf) & 0xFFFFFFFFFFFFF000ULL;
    size_t len = (((size_t)stubbuf) + 68 + 580) - base;
    len = ((len + 0xFFF) >> 12) << 12;
    syscall(10, base, len, 0x7);
    pd.fn_table[0] = (void *) (stubbuf + 0x1c);
    b91tobin(payload, (char const *)payload);
    return ((stub_ptr) stubbuf)(&pd, payload);
}
