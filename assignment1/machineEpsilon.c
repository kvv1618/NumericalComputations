/* epsilon.c  study smallest number added to 1.0 that is not 1.0 */

#include <stdio.h>
double dstore(double tmp);
float store(float tmp);
void sub(float *temp); /* extreme paranoia */

int main()
{
  float eps = 1.0f;
  float temp;
  double deps = 1.0;
  int i;

  printf("epsilon.c running \n");  
  while(1.0+deps>1.0) deps = deps/2.0;
  deps = 2.0*deps; /* went one too many */
  printf("no store double deps=%e \n", deps);

  deps = 1.0;
  while(dstore(1.0+deps)>1.0) deps = deps/2.0;
  deps = 2.0*deps; /* went one too many */
  printf("forced store double deps=%e \n", deps);
  printf("the difference is because of more precision when kept in registers\n");
  printf("Size of double deps: %lu bytes\n", sizeof(deps));

  while(1.0+eps>1.0) eps = eps/2.0;
  eps = 2.0*eps; /* went one too many */
  printf("\nno store float eps=%e \n", eps);

  eps = 1.0f;
  while(store(1.0f+eps)>1.0f) eps = eps/2.0f;
  eps = 2.0f*eps; /* went one too many */
  printf("forced store float eps=%e \n", eps);
  printf("the difference is because of more precision when kept in registers\n");
  printf("Size of float eps: %lu bytes\n", sizeof(eps));

  printf("\nNow float eps, note double when kept in registers \n");
  for(i=1; i<130; i++){
    eps = eps/2.0f;
    temp = (1.0f+eps)-1.0f;
    printf("eps=2^-%d= %e, (1+eps)-1= %e \n", i, eps, temp);
  }
  printf("\nforce store, break optimization \n");
  eps = 1.0f;
  for(i=1; i<155; i++){
    eps = eps/2.0f;
    temp = 1.0f+eps;
    sub(&temp);
    printf("eps=2^-%d= %e, (1+eps)-1= %e \n", i, eps, temp);
  }
  printf("\nend epsilon.c\n");
  return 0;
}

double dstore(double tmp)
{
  return tmp;
}

float store(float tmp)
{
  return tmp;
}

void sub(float *temp)
{
  *temp = *temp - 1.0f;
}