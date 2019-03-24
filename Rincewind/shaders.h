#ifndef _SHADERS
#define _SHADERS

//vertex shaders
//--------------------------------------------------------------------------------------------------------------------------------
const char *firstvert =
"#version 330 core																				    \n"

"layout (location = 0) in vec3 aPos;															    \n"

"void main()																					    \n"
"{																								    \n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);											    \n"
"}																								    \0";
const char *secondvert =
"#version 330 core																					\n"
																									
"layout(location = 0) in vec3 aPos;// the position variable has attribute position 0				\n"
"out vec4 vertexColor; // specify a color output to the fragment shader								\n"
																									
"void main()																						\n"
"{																									\n"
"gl_Position = vec4(aPos, 1.0);// see how we directly give a vec3 to vec4's constructor				\n"
"vertexColor = vec4(0.5, 0.0, 0.0, 1.0);// set the output variable to a dark-red color				\n"
"}																									\n";
const char *thirdvert =																				
"#version 330 core																					\n"
																									
"layout(location = 0) in vec3 aPos;   // the position variable has attribute position 0				\n"
"layout(location = 1) in vec3 aColor; // the color variable has attribute position 1				\n"
																									
"out vec3 ourColor; // output a color to the fragment shader										\n"
																									
"void main()																						\n"
"{																									\n"
"	gl_Position = vec4(aPos, 1.0); 																	\n"
"	ourColor = aColor;// set ourColor to the input color we got from the vertex data				\n"
"}																									\0";
																									
																									
//fragment shaders									
//--------------------------------------------------------------------------------------------------------------------------------
const char *firstfrag =																				
"#version 330 const char *secondfrag =core															\n"
																									
"out vec4 FragColor;																				\n"
																									
"void main()																						\n"
"{																									\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);														\n"
"}																									\0";
const char *secondfrag =																			
"#version 330 core																					\n"
																									
"out vec4 FragColor;																				\n"
"in vec4 vertexColor;  // the input variable from the vertex shader (same name and same type)  		\n"
																									
"void main()																						\n"
"{																									\n"
"	FragColor = vertexColor; 																		\n"
"}																									\0";
const char *thirdfrag =																				
"#version 330 core																					\n"
																									
"out vec4 FragColor; 																				\n"
"uniform vec4 ourColor;  // we set this variable in the OpenGL code.								\n"
																									
"void main()\n																						\n"
"{																									\n"
"	FragColor = ourColor;																			\n"
"}																									\0";
const char *fourthfrag = 																			
"#version 330 core																					\n"
																									
"out vec4 FragColor;																				\n"
"in vec3 ourColor;																					\n"
																									
"void main()																						\n"
"{																									\n"
"	FragColor = vec4(ourColor, 1.0);																\n"
"}																									\0";
#endif