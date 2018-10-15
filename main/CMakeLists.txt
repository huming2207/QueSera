set(COMPONENT_SRCS "QueSeraMain.cpp" "ical/CalLoader.cpp")
set(COMPONENT_ADD_INCLUDEDIRS "." "./ical")
set(COMPONENT_EMBED_TXTFILES "resource/google_root_cert.pem")

register_component()