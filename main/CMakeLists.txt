set(COMPONENT_SRCS "QueSeraMain.cpp"
        "ical/CalLoader.cpp"
        "ical/CalParser.cpp"
        "hal/u8g2_esp32_hal.c"
        "storage/CalStorage.cpp")
set(COMPONENT_ADD_INCLUDEDIRS "." "ical" "hal" "storage")
set(COMPONENT_EMBED_TXTFILES "resource/google_root_cert.pem")

register_component()