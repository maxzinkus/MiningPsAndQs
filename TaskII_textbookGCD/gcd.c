/* Assumes a > b */
int gcd(int a, int b) {
   int temp;

   while(b) {
      temp = b;
      b = a % b;
      a = temp;
   }

   return a;
}
