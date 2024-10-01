<?php
function gcd($a, $b) {
    while ($b != 0) {
        $temp = $b;
        $b = $a % $b;
        $a = $temp;
    }
    return $a;
}
$n = fscanf(STDIN,"%d\n")[0];

for ($i = 0; $i < $n; $i++) {
    $line = trim(fgets(STDIN));
    list($x, $y) = array_map('intval', preg_split('/\s+/', $line));
    fprintf(STDOUT, "%d\n", gcd($x, $y));
}
?>
