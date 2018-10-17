set(COMPONENT_SRCS "QueSeraMain.cpp" "ical/CalLoader.cpp" "ical/CalParser.cpp" "hal/u8g2_esp32_hal.c")
set(COMPONENT_ADD_INCLUDEDIRS "." "ical" "hal")
set(COMPONENT_EMBED_TXTFILES "resource/google_root_cert.pem")

register_component()