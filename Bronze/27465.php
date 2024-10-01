<?php
function isPrime($num) {
    if ($num <= 1) return false; 
    if ($num <= 3) return true;  
    if ($num % 2 == 0 || $num % 3 == 0) return false; 
    
    $i = 5;
    while ($i * $i <= $num) {
        if ($num % $i == 0 || $num % ($i + 2) == 0) return false;
        $i += 6;
    }
    
    return true;
}

fscanf(STDIN,"%d",$a);

while(true){
    if (!isPrime($a)){
        fprintf(STDOUT,"%d",$a);
        break;
    }
    $a++;
}

?>
