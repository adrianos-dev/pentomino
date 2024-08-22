#include<string>
#include<iostream>

// solucion  1: arr1,arr2,arr3,arr4,arr7,arr5,arr6,arr8,arr9,arr10,arr11,arr12 
// solucion  2: arr1,arr2,arr3,arr10,arr4,arr8,arr9,arr6,arr12,arr11,arr5,arr7
// solucion  3: arr1,arr2,arr3,arr9,arr5,arr8,arr10,arr6,arr11,arr4,arr12,arr7
// solucion  4: arr3,arr1,arr8,arr2,arr9,arr11,arr5,arr7,arr10,arr4,arr12,arr6
// solucion  5: arr1,arr2,arr3,arr12,arr7,arr8,arr4,arr5,arr10,arr11,arr9,arr6
// solucion  6: arr3,arr2,arr6,arr10,arr11,arr5,arr1,arr4,arr8,arr9,arr12,arr7
// solucion  7: arr1,arr3,arr6,arr4,arr7,arr2,arr8,arr12,arr10,arr9,arr11,arr5
// solucion  8: arr1,arr2,arr3,arr4,arr8,arr9,arr7,arr5,arr12,arr10,arr11,arr6
// solucion  9: arr11,arr2,arr6,arr3,arr5,arr8,arr4,arr1,arr10,arr12,arr9,arr7
// solucion 10: arr6,arr2,arr5,arr7,arr10,arr12,arr8,arr9,arr11,arr4,arr3,arr1
// solucion 11: arr6,arr1,arr12,arr8,arr2,arr4,arr3,arr10,arr11,arr9,arr5,arr7
// solucion 12: arr1,arr11,arr12,arr4,arr3,arr2,arr8,arr10,arr9,arr7,arr5,arr6
// solucion 13: arr4,arr8,arr11,arr7,arr9,arr12,arr1,arr6,arr5,arr10,arr2,arr3
// solucion 14: arr11,arr3,arr1,arr6,arr8,arr10,arr9,arr2,arr4,arr5,arr12,arr7
// solucion 15: arr5,arr7,arr10,arr6,arr2,arr4,arr11,arr9,arr12,arr8,arr1,arr3
// solucion 16: arr7,arr5,arr11,arr8,arr2,arr1,arr9,arr4,arr6,arr12,arr3,arr10
// solucion 17: arr7,arr3,arr4,arr12,arr11,arr2,arr6,arr5,arr10,arr1,arr8,arr9
// solucion 18: arr1,arr3,arr2,arr8,arr11,arr4,arr9,arr7,arr12,arr10,arr5,arr6
// solucion 19: arr9,arr4,arr6,arr1,arr12,arr7,arr2,arr8,arr10,arr11,arr5,arr3
// solucion 20: arr5,arr9,arr1,arr2,arr4,arr6,arr8,arr10,arr11,arr12,arr3,arr7
// solucion 21: arr1,arr12,arr5,arr10,arr8,arr2,arr7,arr3,arr4,arr9,arr11,arr6
// solucion 22: arr3,arr2,arr6,arr10,arr11,arr5,arr1,arr4,arr8,arr12,arr9,arr7
// solucion 23: arr3,arr2,arr6,arr4,arr9,arr8,arr12,arr1,arr10,arr11,arr5,arr7  
// solucion 24: arr4,arr7,arr5,arr11,arr9,arr6,arr1,arr12,arr2,arr8,arr10,arr3
// solucion 25: arr7,arr5,arr11,arr9,arr6,arr4,arr1,arr12,arr2,arr8,arr10,arr3 // 25 is a variation of 24. 
// solucion 26: arr11,arr2,arr6,arr3,arr5,arr8,arr4,arr1,arr10,arr12,arr9,arr7
// solucion 27: arr6,arr2,arr5,arr7,arr10,arr12,arr8,arr9,arr11,arr4,arr3,arr1
// solucion 28: arr1,arr3,arr6,arr4,arr7,arr2,arr8,arr12,arr10,arr9,arr11,arr5
// solucion 29: arr1,arr6,arr3,arr9,arr8,arr10,arr2,arr5,arr7,arr12,arr4,arr11
// solucion 30: arr1,arr2,arr3,arr4,arr6,arr5,arr7,arr8,arr10,arr9,arr11,arr12 // parecido al 1.
// solucion 31: arr9,arr1,arr8,arr3,arr6,arr5,arr2,arr10,arr7,arr12,arr4,arr11
// solucion 32: arr3,arr12,arr1,arr2,arr8,arr6,arr7,arr10,arr5,arr4,arr9,arr11
// solucion 33: arr3,arr12,arr1,arr2,arr4,arr6,arr9,arr10,arr8,arr5,arr11,arr7
// solucion 34: arr9,arr3,arr7,arr5,arr2,arr4,arr11,arr12,arr8,arr6,arr1,arr10 
// solucion 35: arr3,arr8,arr11,arr2,arr4,arr7,arr5,arr1,arr12,arr10,arr6,arr9
// solucion 36: arr6,arr9,arr2,arr5,arr4,arr11,arr1,arr7,arr10,arr12,arr8,arr3 
// solucion 37: arr1,arr3,arr2,arr8,arr4,arr7,arr9,arr5,arr6,arr10,arr11,arr12 
// solucion 38: arr12,arr6,arr4,arr8,arr5,arr7,arr3,arr2,arr1,arr9,arr10,arr11
// solucion 39: arr3,arr9,arr4,arr1,arr12,arr6,arr10,arr8,arr2,arr11,arr5,arr7 
// solucion 40: arr8,arr12,arr4,arr1,arr5,arr10,arr2,arr7,arr9,arr11,arr6,arr3



extern int arr1[5][2]  = {{0, 0},{1, 0},{2, 0},{0, 1},{2, 1}}; //   1 'u' // 
extern int arr2[5][2]  = {{0, 2},{1, 2},{2, 2},{1, 1},{1, 3}}; //   2 'x' // cruz
extern int arr3[5][2]  = {{0, 0},{0, 1},{0, 2},{1, 0},{2, 0}}; //   3 'L'
extern int arr4[5][2]  = {{0, 0},{0, 1},{-1, 1},{-1, 2},{-2,2}}; // 4  w // tres
extern int arr5[5][2]  = {{0, 0},{1, 0},{2, 0},{1, 1},{1, 2}}; // 5 'T' // capital T
extern int arr6[5][2]  = {{0, 0},{0,1},{1, 1},{2,1},{3, 1}};   //   6 'l' // long small l
extern int arr7[5][2]  = {{0,0},{1,0},{2,0},{3, 0},{4, 0}};    //   7 'I' // el palo largo.
extern int arr8[5][2]  = {{0, 0},{0,1},{1,0},{2,0},{2,-1}};  //     8 'Z' // capital Z
extern int arr9[5][2]  = {{-1, -1},{0, -1},{0, 0},{1, 0},{2, 0}}; // 9 'z' // el zorro z
extern int arr10[5][2] = {{0, 0},{1,0},{0,1},{2,0},{1,-1}};  //     10 's' // siete
extern int arr11[5][2] = {{0,0},{0,1},{1,0},{1,1},{2,0}};    //     11 'D' // 
extern int arr12[5][2] = {{0,0},{1,0},{2,0},{3,0},{2,1}};   //      12 't' // 


