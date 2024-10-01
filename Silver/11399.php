<?php
$n = intval(fgets(STDIN));
$arr = array_map('intval', explode(' ', trim(fgets(STDIN))));
sort($arr);

$res=0;
$sum=0;

foreach($arr as $x){
    $sum+=$x;
    $res+=$sum;
}

echo $res . PHP_EOL;

?>
