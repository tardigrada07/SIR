/*
 ============================================================================
 Name        : SIR.c
 Author      : tardigrada07
 Version     :
 Copyright   : MIT license
 Description : Kermack-McKendrick SIR in C, Ansi-style
 ============================================================================

 N = total population
 t = time
 S = susceptible population (capable of being infected)
 I = infected population
 R = recovered population, no longer infectious (died, recovered)
 c = infection rate
 d = recovery rate (died, recovered)

 */

#include <stdio.h>
#include <stdlib.h>

void draw(double c, double d) {
	char buf[70], buf2[70];
	sprintf(buf,  "set label 'Infection spread rate (c): %.1f' at 5.5,7500", c);
	sprintf(buf2, "set label 'Recovery rate (d): %.1f' at 5.5,7100", d);

	char *cmdGnuplot [] = {"set title \"Kermack-McKendrick SIR simulation\"",
	                       "set xlabel '---- Time --->'",
	                       "set ylabel '---- Population --->'",
						   buf, buf2,
	                       "plot 'sir.txt' u 1:2 w l title 'Susceptible (S)', \
	                             'sir.txt' u 1:3 w l title 'Infected (I)', \
	                             'sir.txt' u 1:4 w l title 'Recovered (R)'"};

	// open GnuPlot with pipe IPC-vel
	FILE *GNUPLOT_Pipe = popen("gnuplot -persist", "w");
	for (int i=0; i<6; i++) {
		fprintf(GNUPLOT_Pipe, "%s \n", cmdGnuplot[i]);
	}
}

int main(void) {
	puts("Kermack-McKendrick SIR simulation");

	double N = 10000.0;
	double S = 9000.0;
	double I = 1000.0;
	double R = 0.0;
	double t = 0.0;
	double c = 2.0;
	double d = 0.2;
	double scale = 0.1;

	// writing to a file
	FILE *f = fopen("sir.txt", "w");

	puts("\nTime\tS\tI\tR");
	for (int i=0; i<100; i++) {
		printf("%.1f\t%.1f\t%.1f\t%.1f\n", t, S, I, R);		// writing to console
		fprintf(f, "%.1f\t%.1f\t%.1f\t%.1f\n", t, S, I, R);	// writing to a file

		double dS = (-c * S * I) / N;
		double dR = d * I;
		double dI = -dS - dR;

		double dt = 1;

		S = S + dS * scale;
		I = I + dI * scale;
		R = R + dR * scale;
		t = t + dt * scale;
	}

	fclose(f);
	draw(c, d);

	return EXIT_SUCCESS;
}
