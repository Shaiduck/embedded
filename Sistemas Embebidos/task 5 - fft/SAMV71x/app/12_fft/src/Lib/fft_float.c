/* ---------------------------------------------------------------------- */


#include "arm_math.h"
#include "arm_const_structs.h"

/** variables for FFT Bin Example */
uint32_t ifftFlag = 0;
uint32_t doBitReverse = 1;
float    scale_factor;

/** Fast fourier transform */
void fft(float * fft_inputData, float * fft_signalPower, uint32_t fftSize, uint32_t * fft_maxPowerIndex, float * fft_maxPower)
{
    uint32_t u32index;
    scale_factor = fftSize;
    const arm_cfft_instance_f32 *cfft_instance;
    
    switch(fftSize)
    {
        case(256):
            cfft_instance = &arm_cfft_sR_f32_len256;
            break;
        case(512):
            cfft_instance = &arm_cfft_sR_f32_len512;
            break;
        case(1024):
            cfft_instance = &arm_cfft_sR_f32_len1024;
            break;
        case(2048):
            cfft_instance = &arm_cfft_sR_f32_len2048;
            break;    
    }  
  /* Process the data through the CFFT/CIFFT module */
    arm_cfft_f32(cfft_instance, fft_inputData, ifftFlag, doBitReverse);

  /*Scale down magnitude */
    for (u32index = 0; u32index <fftSize*2; u32index++)
    {
        fft_inputData[u32index] /= scale_factor;
    }
      
  /* Process the data through the Complex Magnitude Module for calculating the magnitude at each bin */
    arm_cmplx_mag_f32(fft_inputData, fft_signalPower, fftSize);

  /* Calculates maxValue and returns corresponding BIN value */
    arm_max_f32(fft_signalPower, fftSize, fft_maxPower, fft_maxPowerIndex);
}
