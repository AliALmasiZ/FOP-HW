#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
/*****************************/
/*                           */
/*                           */
/*       403100043           */
/*                           */
/*                           */
/*****************************/

#define MALE_MIN 85
#define MALE_MAX 190
#define FEMALE_MIN 165
#define FEMLAE_MAX 300

#define PI 3.14159265358979323846

// Declare your global variables here


struct fourier_element_t
{
    double frequency;
    double magnitude;
};

typedef struct fourier_element_t FourierElement;

struct wave_header_t
{
    uint32_t chunk_id;
    uint32_t chunk_size;
    uint32_t format;
    uint32_t subchunk1_ID;
    uint32_t subchunk1_size;
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_size;
    uint16_t bitsps;
    uint32_t subchunk2_ID;
    uint32_t subchunk2_size;
    // TODO: Implement the wave header structure
    // TODO: You can use the provided structure as a reference
    // TODO: (it's recommended to use stdint.h types, such as uint32_t, uint16_t, etc.)
};


typedef struct wave_header_t WaveHeader;


// TODO: Declare your custom structs here



void fft(double *real, double *imag, unsigned int n)
{
    if (n <= 1)
        return;

    // Divide
    double *evenReal = malloc(n / 2 * sizeof(double));
    double *evenImag = malloc(n / 2 * sizeof(double));
    double *oddReal = malloc(n / 2 * sizeof(double));
    double *oddImag = malloc(n / 2 * sizeof(double));

    for (int i = 0; i < n / 2; i++)
    {
        evenReal[i] = real[i * 2];
        evenImag[i] = imag[i * 2];
        oddReal[i] = real[i * 2 + 1];
        oddImag[i] = imag[i * 2 + 1];
    }

    fft(evenReal, evenImag, n / 2);
    fft(oddReal, oddImag, n / 2);

    // Conquer
    for (int k = 0; k < n / 2; k++)
    {
        const double tReal = cos(-2 * PI * k / n) * oddReal[k] - sin(-2 * PI * k / n) * oddImag[k];
        const double tImag = sin(-2 * PI * k / n) * oddReal[k] + cos(-2 * PI * k / n) * oddImag[k];
        real[k] = evenReal[k] + tReal;
        imag[k] = evenImag[k] + tImag;
        real[k + n / 2] = evenReal[k] - tReal;
        imag[k + n / 2] = evenImag[k] - tImag;
    }

    free(evenReal);
    free(evenImag);
    free(oddReal);
    free(oddImag);
}

// Transform wave data into Frequency domain
// Returns the number of elements in the FourierElement array
unsigned int apply_fourier(FourierElement *dest, void *wave_data, unsigned int size,
                           unsigned int num_channels, unsigned int bit_depth, unsigned int sample_rate)
{
    unsigned int bytes_per_channel = bit_depth / 8;  // TODO: implement this
    unsigned int block_align = bit_depth * num_channels / 8;        // TODO: implement this
    unsigned int num_samples = size / block_align;        // TODO: implement this

    double *real = malloc(num_samples * sizeof(double));
    double *imag = malloc(num_samples * sizeof(double));

    // We only need one channel (using the first one)
    for (int i = 0; i < num_samples; i++)
    {
        uint32_t *sample_ptr = wave_data + i * block_align;
        uint32_t sample = (*sample_ptr) & ((1ULL << bit_depth) - 1); // Keep only the bits that matter
        real[i] = (double)sample;
        imag[i] = 0.0;
    }

    // Apply FFT
    fft(real, imag, num_samples);

    // Calculate magnitudes and frequencies
    for (int i = 0; i < num_samples; i++)
    {
        dest[i].magnitude = sqrt(real[i] * real[i] + imag[i] * imag[i]) / num_samples; // Normalize by size
        dest[i].frequency = (double)i * sample_rate / num_samples;
    }

    free(real);
    free(imag);
    return num_samples;
}

// TODO: You can define your functions here
// TODO: It's recommended to declare function for each command

int main(const int argc, char const *argv[])
{
    if (argc == 1 || argc == 2 || argc > 4)
    {
        printf("Usages: %s <input_wave_file> <command> [output_file]\n", argv[0]);
        printf("Commands:\n");
        printf("\t--info\t\t\tDisplay information about the wave file\n");
        printf("\t--reverse\t\tReverse the wave file\n");
        printf("\t--gender\t\tDetermine the gender of the speaker in the wave file\n");
        printf("\t--double-speed\t\tDouble the speed of the wave file\n");
        printf("\t--double-speed-safe\tDouble the speed (lossless)\n");
        return 1;
    }
    
    const char* wave_path = argv[1];
    // TODO: Open file and parse wav header and read data
    FILE *wave_file = fopen(wave_path, "rb"); 
    WaveHeader wave_header;
    fread(&wave_header, sizeof(WaveHeader), 1, wave_file);

    int num = wave_header.subchunk2_size / wave_header.block_size;
    void *datas = malloc(wave_header.subchunk2_size);
    fread(datas, wave_header.block_size, num, wave_file);
    

    if (!strcmp(argv[2], "--info"))
    {
        if(wave_header.audio_format == 1) {
            printf("Audio Format: PCM\n");
            if(wave_header.num_channels == 1)
                printf("Channels: Mono\n");
            else if(wave_header.num_channels == 2)
                printf("Channels: Stereo\n");
            else
                printf("Channels: Stereo\n");
            printf("%dHz - %d bit\n", wave_header.sample_rate, wave_header.bitsps);
            printf("Length: %d seconds\n", wave_header.subchunk2_size / wave_header.byte_rate);
        }
        else if(wave_header.audio_format == 3)
            printf("Audio Format: IEEE 754 Float\n");
        else if(wave_header.audio_format == 6)
            printf("Audio Format: A-Law\n");
        else if(wave_header.audio_format == 7)
            printf("Audio Format: Mu-Law\n");
        else
            printf("Audio Format: Unknown\n");
        // printf("--%d--\n", wave_header.sample_rate);
        // printf("--%d--\n", wave_header.block_size);
        // printf("--%d--\n", wave_header.byte_rate);
        // printf("--%d--\n", wave_header.bitsps);
        // printf("--%d--\n", wave_header.num_channels);
        // TODO: Implement command 'inafo'
    }
    else if (!strcmp(argv[2], "--reverse"))
    {
        const char* output_path = argv[3];
        FILE *output = fopen(output_path, "wb");
        fwrite(&wave_header, sizeof(wave_header), 1, output);
        for(int i = num - 1 ; i >= 0; i--) {
            fwrite((char*)datas + (i * wave_header.block_size), wave_header.block_size, 1, output);
        }
        fclose(output);
        // TODO: Implement command 'reverse'
    }
    else if (!strcmp(argv[2], "--gender"))
    {
        double male_value = 0, female_value = 0;
        int num_female = 0, num_male = 0;
        FourierElement *samples = (FourierElement*)malloc(sizeof(FourierElement) * num);
        apply_fourier(samples, datas, wave_header.subchunk2_size, wave_header.num_channels, wave_header.bitsps, wave_header.sample_rate);
        for(int i = 0; i < num; i++) {
            if(samples[i].frequency >= 85 && samples[i].frequency <= 190) {
                male_value += samples[i].magnitude;
                num_male++;
            }
            if(samples[i].frequency >= 165 && samples[i].frequency <= 300) {
                female_value += samples[i].magnitude;
                num_female++;
            }
        }
        male_value /= num_male;
        female_value /= num_female;
        const char *gender;
        double value;
        if(male_value > female_value) {
            gender = "Male";
            value = male_value / female_value;
        }
        else {
            gender = "Female";
            value = female_value / male_value;
        }
        printf("%s (Value: %.2lf)\n", gender, value);
        // TODO: Implement gender recognition using apply_fourier on wav data
    }
    else if (!strcmp(argv[2], "--double-speed"))
    {
        int new_num = num / 2;
        void *new_data = malloc(new_num * wave_header.block_size);
        for(int i = 0; i < new_num; i++) {
            memcpy((char *)new_data + (i * wave_header.block_size), (char *)datas + (2 * i * wave_header.block_size), wave_header.block_size);
        }
        wave_header.subchunk2_size = new_num * wave_header.block_size;
        wave_header.chunk_size = wave_header.subchunk2_size + 36;


        const char* output_path = argv[3];
        FILE *output = fopen(output_path, "wb");
        fwrite(&wave_header, sizeof(wave_header), 1, output);
        fwrite(new_data, wave_header.block_size, new_num, output);
        fclose(output);
        // TODO: Implement command 'double-speed' with loss
        // You have to remove every other sample
        // and write the new wave file
    }
    else if (!strcmp(argv[2], "--double-speed-safe"))
    {
        wave_header.sample_rate *= 2;
        wave_header.byte_rate *= 2;


        const char* output_path = argv[3];
        FILE *output = fopen(output_path, "wb");
        fwrite(&wave_header, sizeof(wave_header), 1, output);
        fwrite(datas, wave_header.block_size, num, output);
        fclose(output);
        // TODO: Implement command 'double-speed-safe' without loss
        // You have to double the sample rate and write the new wave file
    }
    else
    {
        printf("Invalid command\n");
        // TODO: Free your dynamically allocated memory
        return 1;
    }
    // TODO: Free your dynamically allocated memory
    fclose(wave_file);
    free(datas);


    return 0;
}
