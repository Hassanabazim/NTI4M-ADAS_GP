
#ifndef RPLIDAR_INTERFACE_H_
#define RPLIDAR_INTERFACE_H_

typedef enum{
	OK=0,
	NOK
}Check_error_t;
typedef struct
{
	float angle;
	float distance;
}Scan_response_t;

void RPLIDAR_voidScanResponse(float angle1, float angle2);
void func_check(void);
void RPLIDAR_voidINT(void);
Check_error_t RPLIDAR_DescriptorCheck(void);
float RPLIDAR_GetDistanceValue(float angle1, float angle2);

#endif
