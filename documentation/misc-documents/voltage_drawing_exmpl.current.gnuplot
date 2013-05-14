set table "voltage_drawing_exmpl.current.table"; set format "%.5f"
set samples 100; plot [x=0:7] 1.8*sin(x+90*3.141592654/180)
