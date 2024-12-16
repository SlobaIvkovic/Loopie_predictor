Prerequisites: download libcurl prebuilt binaries at https://curl.se/download.html. Make sure that binaries are 32 bit,
since this is devCpp project hence compiled into 32bit program.

Set devCpp project include and lib directory options to match the folders inside project folder, add all .a libs inside
linker parameters. Or alternativelly cratate a custom makefile with all these settings.

 Take include and lib folders and copy them to the project
parrent directory. Acquire SSL certificate file and place it inside EXECUTABLE folder
and finaly place libcurl.dll inside EXECUTABLE folder.
