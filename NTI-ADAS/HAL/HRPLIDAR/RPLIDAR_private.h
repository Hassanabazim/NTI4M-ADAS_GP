

#ifndef RPLIDAR_PRIVATE_H_
#define RPLIDAR_PRIVATE_H_

u8 Copy_uint8ARRGetHealt[10]={0xa5,0x5a,0x03,0x00,0x00,0x00,0x06};
u8 Copy_uint8ARRScanResponse[7] ={ 0xa5, 0x5a, 0x05, 0x00, 0x00, 0x40, 0x81 };

static Check_error_t RPLIDAR_Check_error_tGetHealth(void);
static Check_error_t RPLIDAR_GetDescriptor(void);

#endif
