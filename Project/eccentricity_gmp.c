#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main(int argc, char *argv[]) {

    mpf_set_default_prec(128);

    // Open the CSV file
    FILE *file = fopen("RawData/horizons_results_30_years.csv", "r");
    if (file == NULL) {
        printf("Error: File not found\n");
        return 1;
    }

    // Skip the first line and store the 1st, 2nd, 3rd columns in arrays
    char line[150];
    fgets(line, 100, file);

    // Declare GMP variables for position coordinates
    mpf_t position_x[12000], position_y[12000], position_z[12000];
    for (int i = 0; i < 12000; i++) {
        mpf_init(position_x[i]);
        mpf_init(position_y[i]);
        mpf_init(position_z[i]);
    }

    int i = 0;
    while (fgets(line, 150, file)) {
        // Read the 2nd, 3rd, and 4th columns (position values)
        // Using %s to read as string and then converting to mpf_t using mpf_set_str
        char x_str[50], y_str[50], z_str[50];
        sscanf(line, "%*[^,],%49[^,],%49[^,],%49[^,]", x_str, y_str, z_str);

        mpf_set_str(position_x[i], x_str, 10);  // base 10 conversion to GMP type
        mpf_set_str(position_y[i], y_str, 10);  // base 10 conversion to GMP type
        mpf_set_str(position_z[i], z_str, 10);  // base 10 conversion to GMP type
        i++;
    }
    fclose(file);

    // Declare GMP variables for min and max magnitudes
    mpf_t min_mag, max_mag, mag;
    mpf_init(min_mag);
    mpf_init(max_mag);
    mpf_init(mag);

    // Initialize min and max magnitudes
    mpf_set_d(min_mag, 0);
    mpf_set_d(max_mag, 0);

    // Calculate the magnitudes and find min and max
    for (int j = 0; j < i; j++) {
        mpf_t x_sq, y_sq, z_sq;
        mpf_init(x_sq);
        mpf_init(y_sq);
        mpf_init(z_sq);

        mpf_mul(x_sq, position_x[j], position_x[j]);  // x^2
        mpf_mul(y_sq, position_y[j], position_y[j]);  // y^2
        mpf_mul(z_sq, position_z[j], position_z[j]);  // z^2

        mpf_add(mag, x_sq, y_sq);  // mag = x^2 + y^2
        mpf_add(mag, mag, z_sq);   // mag += z^2

        mpf_sqrt(mag, mag);  // mag = sqrt(x^2 + y^2 + z^2)

        if (j == 0) {
            mpf_set(min_mag, mag);
            mpf_set(max_mag, mag);
        } else {
            // Compare with min and max
            if (mpf_cmp(mag, min_mag) < 0) {
                mpf_set(min_mag, mag);
            }
            if (mpf_cmp(mag, max_mag) > 0) {
                mpf_set(max_mag, mag);
            }
        }

        mpf_clear(x_sq);
        mpf_clear(y_sq);
        mpf_clear(z_sq);
    }

    // Calculate the result: (max_mag - min_mag) / (max_mag + min_mag)
    mpf_t result, denom;
    mpf_init(result);
    mpf_init(denom);

    //Convert to AU
    mpf_t au;
    mpf_init(au);
    mpf_set_d(au, 149597870.691);

    mpf_div(min_mag, min_mag, au);
    mpf_div(max_mag, max_mag, au);

    //print max and min magnitudes
    gmp_printf("Max magnitude: %.20Ff\n", max_mag);
    gmp_printf("Min magnitude: %.20Ff\n", min_mag);

    mpf_add(denom, max_mag, min_mag);  // denom = max_mag + min_mag
    mpf_sub(result, max_mag, min_mag); // result = max_mag - min_mag
    mpf_div(result, result, denom);    // result = (max_mag - min_mag) / (max_mag + min_mag)
    
    // Print the result
    gmp_printf("Result: %.20Ff\n", result);

    // Clear GMP variables
    mpf_clear(min_mag);
    mpf_clear(max_mag);
    mpf_clear(mag);
    mpf_clear(result);
    mpf_clear(denom);

    // Clear position arrays
    for (int j = 0; j < 12000; j++) {
        mpf_clear(position_x[j]);
        mpf_clear(position_y[j]);
        mpf_clear(position_z[j]);
    }

    return 0;
}
