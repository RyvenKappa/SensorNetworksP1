Port = "15"
Confirm=false
DevEUI = resiot_comm_getparam("deveuisource")
AppEUI = resiot_comm_getparam("appeuisource")
Payload="0104"
Error = resiot_tx(Payload, Port, DevEUI, AppEUI, "", "",Confirm, "")
if Error ~="" then
	resiot_debug(string.format("SN_Z_Command_Red Tx Error: %s\n", Error))
end