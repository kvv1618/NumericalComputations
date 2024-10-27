/********************************
Rocket Science
Tyler Simon
Engine thrust data available at
http://www.nar.org/SandT/NARenglist.shtml

Estes Alpha III
Length      12.25  inches =  0.311 meters
Diameter     0.95  inches =  0.0241 meters
Body area    0.785 square inches = 0.506E-3  square meters cross section
Cd of body   0.45  dimensionless
Fins area    7.69  square inches = 0.00496  square meters total for 3 fins
Cd of fins   0.01  dimensionless
Weight/mass  1.2   ounce  = 0.0340 kilogram without engine
Engine       0.85  ounce  = 0.0242 kilogram initial engine mass
Engine       0.33  ounce  = 0.0094 kilogram final engine mass

Thrust curve
Total impulse  8.82 newton seconds (area under curve)
Peak thrust   14.09 newton
Average thrust 4.74 newton
Burn time      1.86 second

To compile: cc -o rocket rocket.c -lm
To Run: ./rocket

************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_TH 2.0
#define dt 0.1 

int main(int argc, char** argv)
{

/*Basic physics:*/
float F;   // F is force in newtons
float m;   // m is mass in kilograms,
float a;   // a is acceleration in m/s/s
float dv;  // velocity change in m/s
float ds;  // distance in meters moved in dt
float vp;  // velocity prior to dt
float v;   // velocity after dt
float s;   // new position after dt
float sp;  // previos position prior to dt  
float Cd;  // coefficient of drag
float Fg;  // gravitational force toward earth
float Fd;  //force of drag in N in direction opposite to velocity

/*Measured values for thrust*/
/*Taken from website*/
float thrust[25]={0,6,14.1,5.5,4.5,4.3,4.3,4.3,4.3,4.3,4.3,4.1,4.1,4.3,4.3,4.3,4.3,4.5,4.5,0};

/*Physical Constants*/
float rho = 1.293; /*density of Air in m^3*/
float g = 9.80665; /*meters per sec^2*/
float mass=0.0340; /*kilogram without engine*/
float engine_m= 0.0242; /*kilogram initial engine mass*/
float engine_f = 0.0094; /*kilogram final engine mass*/
float Cd_fin=0.01;   /*drag coefficient of fins*/
float Area_fin=0.496E-2; /*sq meters of fin areai total for 3 fins*/
float Cd_body=0.45;      /*Coefficient of drag for body*/
float Area_body=0.506E-3; /*Area of body cross section sq meters*/


/*Initialize Variables*/
int index=0;
float time=0.0;
float t_sum=0.0;
float dmass=0.0;
float Fd_fins=0.0;
float Fd_body=0.0;
v=vp=0.0;
s=sp=0.0;

/*check the sum of thrust, and rate engine loses mass "degrades"*/
for (index=0; index<=(MAX_TH/dt);index++)
{
t_sum+=thrust[index];
}
float thr_degrade=(engine_m-engine_f)/t_sum;
printf("#thr_degrade %f\n#t_sum %f\n", thr_degrade,t_sum); 
printf("#avg_thrust %f\n", t_sum/(MAX_TH/dt)); 

printf("#\n");
printf("#time(s) height(m) velocity(m/s) acc(m/s)^2 force(N) mass(kg) thrust(N)\n");

index=0;

/*Begin Time Stepping, stop when velocity is negative*/
while(vp>=0.0)
	{
	engine_m-=thr_degrade*thrust[index];
	dmass=mass+engine_m;
        Fg=dmass*g;  
        Fd_fins=(Cd_fin*rho*Area_fin*pow(v,2))/2;
        Fd_body=(Cd_body*rho*Area_body*pow(v,2))/2;
	F=thrust[index]-(Fg+Fd_fins+Fd_body);
	//F=thrust[index];

	if (time==0) a=0.0; //sitting on the launch pad
	else a=F/dmass;     //else in the air

	dv=a*dt;	
	v=vp+dv;
  	ds=v*dt;
  	s=sp+ds; 
	printf("%1.1f %f %f %f %2.2f %f %f\n", time, s, v, a, F, dmass, thrust[index]);

	time+=dt;
	vp=v;
	sp=s;
	if (index<=(MAX_TH/dt))index++;

	}
/*End time Stepping*/

return 0;
}
/*End Main*/
