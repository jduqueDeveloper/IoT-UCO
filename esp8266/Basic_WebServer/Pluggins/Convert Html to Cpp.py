#!/usr/bin/env python
# coding: utf-8


# This code allow to generate a C string that contain elements of web page
# How to use:
#	1. copy .html file into the same folder
#	2. run this sctipt

# Designed by Juan Diego Cardona Marín 27-02-2019



f = open("./index.html", "r")
varName = 'WebPage'

output =  '#include "WString.h"\n'
output += '#include "web_page.h"\n\n'
output += 'String {} = \"\";\n\n'.format(varName)
output += 'void generate_page(){\n'

for line in f:
    line = line.split("\n")[0]
    line = line.replace("\"","\'")    
    if(line != ""):
        output = output + "\t{} += \"{}\";\n".format(varName,line) 
output += '}'



# Write  .c  File
index_fixed = open("./web_page.cpp", "w")
index_fixed.write(output)
index_fixed.close()



#Generate .h File

output_h =  """#ifndef WEB_PAGE_H
#define WEB_PAGE_H
#include "WString.h"

extern String WebPage;
extern void generate_page();

#endif"""


# Write  .h  File
index_fixed = open("./web_page.h", "w")
index_fixed.write(output_h)
index_fixed.close()
