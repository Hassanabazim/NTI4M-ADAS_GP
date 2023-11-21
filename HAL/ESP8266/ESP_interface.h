
#ifndef ESP_INTERFACE_H
#define ESP_INTERFACE_H

ErrorState_t ESP_voidInit(void);
ErrorState_t ESP_VoidConnectToWiFi(u8 *Copy_name , u8 *Copy_pass);
void ESP_VidConnectToSrvTcp (u8 *Copy_u8Domain , u8 *Copy_u8Port);
ErrorState_t ESP_u8ReceiveHttpReq(u8 *Copy_u8ChannelID , u8 *Copy_u8Length, u8 *data);

#endif
