#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define HASHMASK 0xFFFF


uint64_t hash(const char* key, uint64_t seed)
{
    uint64_t i;

    for (i = 0; *key; key++, i++) {
	   seed ^= ((seed << 5) + (*key) + (seed >> 2));
    }
    seed &= HASHMASK;
    return seed;
}


uint64_t addBloom(char* word, uint64_t oldBloom) {
  
  int k[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
  
  for (int i =0 ; i< 10 ; i++) {
    oldBloom |= 2 << hash(word, k[i]);
  }
  
 
  //printf("%lX\n",oldBloom);
  return oldBloom;
 
}

void checkBloom(char* word, uint64_t oldBloom) {
  
  int k[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
  int found = 1;
  
  for (int i =0 ; i< 10 ; i++) {
    uint64_t h = 2 << hash(word, k[i]);
    if ((oldBloom & h) != h) found = 0;
  }
  
  printf("%s: %d\n", word, found);
 
}


int main(int argc, int** argv) {
  
  uint64_t bloom = 0;
   
  bloom = addBloom("hello", bloom);
  bloom = addBloom("world", bloom);
  bloom = addBloom("from", bloom);
  bloom = addBloom("west", bloom);
  bloom = addBloom("london", bloom);
  bloom = addBloom("hack", bloom);
  bloom = addBloom("night", bloom);
  
  //printf("%lX\n",bloom);
  
  checkBloom("badger", bloom);
  
  checkBloom("hack", bloom);
  checkBloom("hello", bloom);
  checkBloom("anotherword", bloom);
  checkBloom("night", bloom);

}