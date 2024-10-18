MAIN: add r3, LIST 
LOOP: prn #48 
   lea STR, r6 
 inc r6 
mov    r3, K 
sub  r1,    r4   
   bne   END   
   mcro  a_mc  
cmp     K, #-6 
   bne &END 
mcroend  
mcro  b_mc  
cmp     K, #-6BBB
   bne &END 
mcroend  
mcro  c_mc  
cmp     K, #-6CCC 
   bne &END 
mcroend  
cmp K, #-6 
bne   &END    
dec   K  
jmp &LOOP 
a_mc
b_mc
c_mc

END:    stop 
STR: .string “abcd” 
LIST: .data 6, -9 
.data    -100 
K: .data 31 

 