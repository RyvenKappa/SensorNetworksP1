function parsePayload(appeui,deveui,payload)
  	raw_payload = payload
  	payload = resiot_hexdecode(payload)
  	header = payload[1]
  	--El primer byte del payload es un header
  
	latitude = resiot_ba2float32LE({payload[2],payload[3],payload[4],payload[5]})
  	worked, err = resiot_setnodevalue(appeui, deveui, "Latitude", latitude)
	longitude = resiot_ba2float32LE({payload[6],payload[7],payload[8],payload[9]})
  	worked, err = resiot_setnodevalue(appeui, deveui, "Longitude", longitude)
  	altitude = resiot_ba2intLE16({payload[10],payload[11]})
  	worked, err = resiot_setnodevalue(appeui, deveui, "Altitude", altitude)
  
  
  
  	clear = resiot_ba2intLE16({payload[12],payload[13]})
  	worked, err = resiot_setnodevalue(appeui, deveui, "Clear", clear)
  
  	red = resiot_ba2intLE16({payload[14],payload[15]})
  	worked, err = resiot_setnodevalue(appeui, deveui, "Red", red)	
  
  	green = resiot_ba2intLE16({payload[16],payload[17]})
  	worked, err = resiot_setnodevalue(appeui, deveui, "Green", green)
  
  	blue = resiot_ba2intLE16({payload[18],payload[19]})
  	worked, err = resiot_setnodevalue(appeui, deveui, "Blue", blue)
  
  	raw_temp = resiot_int16(resiot_ba2intLE16({payload[20],payload[21]}))
    temp = (175.72*raw_temp/65536.0)-46.85
  	temp = tonumber(string.format("%.2f", temp))
  	worked, err = resiot_setnodevalue(appeui, deveui, "Temperature", temp)
  
  	--Empieza la parte NO alineada
  	--la humedad esta en porcentaje multiplicado por 10, usando 10 bits
	raw_humidity_bytes = resiot_ba2intLE16({payload[22],payload[23]})
  	masked_humidity = resiot_and64(0x03FF,raw_humidity_bytes)--Mascara de 10 bits
  	humidity = tonumber(string.format("%.2f", (masked_humidity/10.0)))
  	worked, err = resiot_setnodevalue(appeui, deveui, "Humidity", humidity)
  	
  	--Accelerometer
  	raw_Xacc_bytes = resiot_int16(resiot_ba2intLE16({payload[23],payload[24]}))
  	masked_Xacc = (resiot_int16(resiot_and64(0xFFFC,raw_Xacc_bytes))/4)
  	x_acc = masked_Xacc*9.80665/1024.0
  	worked, err = resiot_setnodevalue(appeui, deveui, "X_acc", x_acc)
  	--resiot_debug(x_acc)
  
  	--Nueva parte-------
  	--Luz esta en porcentaje multiplicado por 10, usando 10 bits
	raw_light_bytes = resiot_ba2intLE16({payload[25],payload[26]})
  	masked_light = resiot_and64(0x03FF,raw_light_bytes)--Mascara de 10 bits
  	light = tonumber(string.format("%.2f", (masked_light/10.0)))
  	worked, err = resiot_setnodevalue(appeui, deveui, "Light", light)
  
  	raw_Yacc_bytes = resiot_int16(resiot_ba2intLE16({payload[26],payload[27]}))
  	masked_Yacc = (resiot_int16(resiot_and64(0xFFFC,raw_Yacc_bytes))/4)
  	y_acc = masked_Yacc*9.80665/1024.0
  	worked, err = resiot_setnodevalue(appeui, deveui, "Y_acc", y_acc)
  	--resiot_debug(y_acc)
 
   	--Moisture esta en porcentaje multiplicado por 10, usando 10 bits
	raw_moisture_bytes = resiot_ba2intLE16({payload[28],payload[29]})
  	masked_moisture = resiot_and64(0x03FF,raw_moisture_bytes)--Mascara de 10 bits
  	moisture = tonumber(string.format("%.2f", (masked_moisture/10.0)))
  	worked, err = resiot_setnodevalue(appeui, deveui, "Moisture", moisture)
  
  	raw_Zacc_bytes = resiot_int16(resiot_ba2intLE16({payload[29],payload[30]}))
  	masked_Zacc = (resiot_int16(resiot_and64(0xFFFC,raw_Zacc_bytes))/4)
  	z_acc = masked_Zacc*9.80665/1024.0
  	worked, err = resiot_setnodevalue(appeui, deveui, "Z_acc", z_acc)
  	--resiot_debug(y_acc)
  
  	-------------Anitgua estructura
  	--raw_Yacc_bytes = resiot_int16(resiot_ba2intLE16({payload[25],payload[26]}))
  	--masked_Yacc = (resiot_int16(resiot_and64(0x3FFF,raw_Yacc_bytes)*4))/4
  	--y_acc = masked_Yacc*9.80665/1024.0
  	--worked, err = resiot_setnodevalue(appeui, deveui, "Y_acc", y_acc)
  	--resiot_debug(y_acc)
  
  	--Z_raw = resiot_ba2intLE32({payload[26],payload[27],payload[28],0xFF})
  	--masked_z_raw = resiot_int16(resiot_and64(0x000FFFC0,Z_raw)/(2^2))
  	--shifted_z_raw = masked_z_raw/(2^4)
  	--z_value = resiot_int16(shifted_z_raw)
  	--z_acc = z_value*9.80665/1024.0
 	--worked, err = resiot_setnodevalue(appeui, deveui, "Z_acc", z_acc)
  	--resiot_debug(z_acc)
  
  	--light_raw = resiot_ba2intLE16({payload[28],payload[29]})
  	--masked_light_raw = resiot_and64(0x0FFC,light_raw)
  	--resiot_debug(light_raw)
  	--shifted_light_raw = masked_light_raw/4.0
  	--light = shifted_light_raw/10.0
  	--worked, err = resiot_setnodevalue(appeui, deveui, "Light", light)
  
  	--moisture_raw = resiot_ba2intLE16({payload[29],payload[30]})
  	--masked_moisture_raw = resiot_and64(0xFFC0,moisture_raw)
  	--shifted_moisture_raw = masked_moisture_raw/(2^6)
  	--moisture = shifted_moisture_raw/10.0
  	--worked, err = resiot_setnodevalue(appeui, deveui, "Moisture", moisture)
end

Origin = resiot_startfrom()

if Origin == "Manual" then
  payload = "00488b21420c0367c0bc02dd6e2922792bb12b285e4da2fe10d80200b8f0"
  appeui = "70b3d57ed000ac4a"
  deveui = "7139323559379194"
else
  appeui = resiot_comm_getparam("appeui")
  deveui = resiot_comm_getparam("deveui")
  payload, err = resiot_getlastpayload(appeui, deveui)
  resiot_debug("SN_TEST_GG Test Auto Mode\n")
end
parsePayload(appeui,deveui,payload)