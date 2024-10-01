<?php
function factorial($num,$mod){
    $res=1;
    for ($i=2;$i<$num+1;$i++){
        $res=($res*$i)%$mod;
    }
    return $res;
}

fscanf(STDIN,"%d %d",$a,$b);
fprintf(STDOUT,"%d",factorial($a,$b));

?>
