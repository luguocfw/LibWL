@echo off

set gyp_tools_dir=GYP-Tools\

if exist %gyp_tools_dir% (
	echo dirent : %gyp_tools_dir% already exist
) else (
	git clone https://github.com/luguocfw/GYP-Tools
)
