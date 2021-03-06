# Alternative GNU Make project makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild

SHELLTYPE := posix
ifeq (.exe,$(findstring .exe,$(ComSpec)))
	SHELLTYPE := msdos
endif

# Configurations
# #############################################

RESCOMP = windres
PCH = src/pch.h
PCH_PLACEHOLDER = $(OBJDIR)/$(notdir $(PCH))
GCH = $(PCH_PLACEHOLDER).gch
INCLUDES += -Isrc -Ivendor/spdlog/include -Ivendor/GLFW/include -Ivendor/Glad/include -Ivendor/ImGui -Ivendor/glm/glm -Ivendor/Nuklear -Ivendor/entt/single_include -Ivendor/tinyobjloader
FORCE_INCLUDE +=
ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
LINKCMD = $(AR) -rcs "$@" $(OBJECTS)
define PREBUILDCMDS
endef
define PRELINKCMDS
endef
define POSTBUILDCMDS
endef

ifeq ($(config),debug)
TARGETDIR = ../bin/Debug-linux-x86_64/Swan
TARGET = $(TARGETDIR)/libSwan.a
OBJDIR = ../bin-int/Debug-linux-x86_64/Swan
DEFINES += -D_CRT_SECURE_NO_WARNINGS -DGLFW_INCLUDE_NONE -DSW_PLATFORM_LINUX -DSW_BUILD_DLL -DDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -g
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -g -std=c++17
LIBS += vendor/GLFW/bin/Debug-linux-x86_64/GLFW/libGLFW.a vendor/Glad/bin/Debug-linux-x86_64/Glad/libGlad.a vendor/ImGui/bin/Debug-linux-x86_64/ImGui/libImGui.a -ldl -lGL
LDDEPS += vendor/GLFW/bin/Debug-linux-x86_64/GLFW/libGLFW.a vendor/Glad/bin/Debug-linux-x86_64/Glad/libGlad.a vendor/ImGui/bin/Debug-linux-x86_64/ImGui/libImGui.a
ALL_LDFLAGS += $(LDFLAGS) -L/usr/lib64 -m64 -pthread

else ifeq ($(config),release)
TARGETDIR = ../bin/Release-linux-x86_64/Swan
TARGET = $(TARGETDIR)/libSwan.a
OBJDIR = ../bin-int/Release-linux-x86_64/Swan
DEFINES += -D_CRT_SECURE_NO_WARNINGS -DGLFW_INCLUDE_NONE -DSW_PLATFORM_LINUX -DSW_BUILD_DLL -DRDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -O2
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -O2 -std=c++17
LIBS += vendor/GLFW/bin/Release-linux-x86_64/GLFW/libGLFW.a vendor/Glad/bin/Release-linux-x86_64/Glad/libGlad.a vendor/ImGui/bin/Release-linux-x86_64/ImGui/libImGui.a -ldl -lGL
LDDEPS += vendor/GLFW/bin/Release-linux-x86_64/GLFW/libGLFW.a vendor/Glad/bin/Release-linux-x86_64/Glad/libGlad.a vendor/ImGui/bin/Release-linux-x86_64/ImGui/libImGui.a
ALL_LDFLAGS += $(LDFLAGS) -L/usr/lib64 -m64 -s -pthread

else ifeq ($(config),dist)
TARGETDIR = ../bin/Dist-linux-x86_64/Swan
TARGET = $(TARGETDIR)/libSwan.a
OBJDIR = ../bin-int/Dist-linux-x86_64/Swan
DEFINES += -D_CRT_SECURE_NO_WARNINGS -DGLFW_INCLUDE_NONE -DSW_PLATFORM_LINUX -DSW_BUILD_DLL -DNDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -O2
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -O2 -std=c++17
LIBS += vendor/GLFW/bin/Dist-linux-x86_64/GLFW/libGLFW.a vendor/Glad/bin/Dist-linux-x86_64/Glad/libGlad.a vendor/ImGui/bin/Dist-linux-x86_64/ImGui/libImGui.a -ldl -lGL
LDDEPS += vendor/GLFW/bin/Dist-linux-x86_64/GLFW/libGLFW.a vendor/Glad/bin/Dist-linux-x86_64/Glad/libGlad.a vendor/ImGui/bin/Dist-linux-x86_64/ImGui/libImGui.a
ALL_LDFLAGS += $(LDFLAGS) -L/usr/lib64 -m64 -s -pthread

endif

# Per File Configurations
# #############################################


# File sets
# #############################################

GENERATED :=
OBJECTS :=

GENERATED += $(OBJDIR)/Application.o
GENERATED += $(OBJDIR)/Buffer.o
GENERATED += $(OBJDIR)/Camera.o
GENERATED += $(OBJDIR)/Framebuffer.o
GENERATED += $(OBJDIR)/GuiLayer.o
GENERATED += $(OBJDIR)/ImGuiBuild.o
GENERATED += $(OBJDIR)/LayerStack.o
GENERATED += $(OBJDIR)/Mesh.o
GENERATED += $(OBJDIR)/Renderer.o
GENERATED += $(OBJDIR)/Scene.o
GENERATED += $(OBJDIR)/Shader.o
GENERATED += $(OBJDIR)/Texture.o
GENERATED += $(OBJDIR)/VertexArray.o
GENERATED += $(OBJDIR)/Window.o
GENERATED += $(OBJDIR)/stb_image.o
GENERATED += $(OBJDIR)/tiny_obj_loader.o
OBJECTS += $(OBJDIR)/Application.o
OBJECTS += $(OBJDIR)/Buffer.o
OBJECTS += $(OBJDIR)/Camera.o
OBJECTS += $(OBJDIR)/Framebuffer.o
OBJECTS += $(OBJDIR)/GuiLayer.o
OBJECTS += $(OBJDIR)/ImGuiBuild.o
OBJECTS += $(OBJDIR)/LayerStack.o
OBJECTS += $(OBJDIR)/Mesh.o
OBJECTS += $(OBJDIR)/Renderer.o
OBJECTS += $(OBJDIR)/Scene.o
OBJECTS += $(OBJDIR)/Shader.o
OBJECTS += $(OBJDIR)/Texture.o
OBJECTS += $(OBJDIR)/VertexArray.o
OBJECTS += $(OBJDIR)/Window.o
OBJECTS += $(OBJDIR)/stb_image.o
OBJECTS += $(OBJDIR)/tiny_obj_loader.o

# Rules
# #############################################

all: $(TARGET)
	@:

$(TARGET): $(GENERATED) $(OBJECTS) $(LDDEPS) | $(TARGETDIR)
	$(PRELINKCMDS)
	@echo Linking Swan
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning Swan
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(GENERATED)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(GENERATED)) rmdir /s /q $(subst /,\\,$(GENERATED))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild: | $(OBJDIR)
	$(PREBUILDCMDS)

ifneq (,$(PCH))
$(OBJECTS): $(GCH) | $(PCH_PLACEHOLDER)
$(GCH): $(PCH) | prebuild
	@echo $(notdir $<)
	$(SILENT) $(CXX) -x c++-header $(ALL_CXXFLAGS) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
$(PCH_PLACEHOLDER): $(GCH) | $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) touch "$@"
else
	$(SILENT) echo $null >> "$@"
endif
else
$(OBJECTS): | prebuild
endif


# File Rules
# #############################################

$(OBJDIR)/Application.o: src/Base/Application.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) -include $(PCH_PLACEHOLDER) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/LayerStack.o: src/Base/LayerStack.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) -include $(PCH_PLACEHOLDER) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Window.o: src/Base/Window.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) -include $(PCH_PLACEHOLDER) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/GuiLayer.o: src/GUI/GuiLayer.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) -include $(PCH_PLACEHOLDER) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/ImGuiBuild.o: src/GUI/ImGuiBuild.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) -include $(PCH_PLACEHOLDER) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Buffer.o: src/Renderer/Buffer.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) -include $(PCH_PLACEHOLDER) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Camera.o: src/Renderer/Camera.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) -include $(PCH_PLACEHOLDER) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Framebuffer.o: src/Renderer/Framebuffer.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) -include $(PCH_PLACEHOLDER) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Mesh.o: src/Renderer/Mesh.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) -include $(PCH_PLACEHOLDER) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Renderer.o: src/Renderer/Renderer.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) -include $(PCH_PLACEHOLDER) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Shader.o: src/Renderer/Shader.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) -include $(PCH_PLACEHOLDER) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Texture.o: src/Renderer/Texture.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) -include $(PCH_PLACEHOLDER) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/VertexArray.o: src/Renderer/VertexArray.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) -include $(PCH_PLACEHOLDER) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Scene.o: src/Scene/Scene.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) -include $(PCH_PLACEHOLDER) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/stb_image.o: src/Utils/stb_image.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) -include $(PCH_PLACEHOLDER) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/tiny_obj_loader.o: vendor/tinyobjloader/tiny_obj_loader.cc
	@echo $(notdir $<)
	$(SILENT) $(CXX) -include $(PCH_PLACEHOLDER) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(PCH_PLACEHOLDER).d
endif