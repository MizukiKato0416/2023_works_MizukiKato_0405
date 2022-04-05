xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 504;
 -8.76716;45.00298;-21.99953;,
 8.85228;45.00298;-21.99953;,
 18.19945;31.78117;-31.34673;,
 -18.11435;31.78117;-31.34673;,
 8.85228;45.00298;-21.99953;,
 8.85228;45.00298;-4.38009;,
 18.19945;31.78117;4.96708;,
 18.19945;31.78117;-31.34673;,
 -8.76716;45.00298;-4.38009;,
 -8.76716;45.00298;-21.99953;,
 -18.11435;31.78117;-31.34673;,
 -18.11435;31.78117;4.96708;,
 8.85228;45.00298;-21.99953;,
 -8.76716;45.00298;-21.99953;,
 2.84371;39.65500;-31.48063;,
 2.84371;39.65500;-21.16904;,
 2.84371;33.94729;-21.16904;,
 2.84371;33.94729;-31.48063;,
 -2.86400;39.65500;-21.16904;,
 -2.86400;39.65500;-31.48063;,
 -2.86400;33.94729;-31.48063;,
 -2.86400;33.94729;-21.16904;,
 2.84371;39.65500;-31.48063;,
 -2.86400;39.65500;-31.48063;,
 -2.77580;39.62557;-30.65018;,
 2.62722;39.62557;-30.65018;,
 2.62722;34.22263;-30.65018;,
 -2.77580;34.22263;-30.65018;,
 -18.20513;30.58903;-31.44416;,
 18.29023;30.58903;-31.44416;,
 22.88172;22.04988;-36.03566;,
 -22.79661;22.04988;-36.03566;,
 22.88172;9.82396;-36.03566;,
 -22.79661;9.82396;-36.03566;,
 18.29023;1.28483;-31.44416;,
 -18.20513;1.28483;-31.44416;,
 18.29023;30.58903;-31.44416;,
 18.29023;30.58903;5.05120;,
 22.88172;22.04988;9.64267;,
 22.88172;22.04988;-36.03566;,
 22.88172;9.82396;11.59921;,
 22.88172;9.82396;-36.03566;,
 18.29023;1.28483;7.00771;,
 18.29023;1.28483;-31.44416;,
 -18.20513;30.58903;5.05120;,
 -18.20513;30.58903;-31.44416;,
 -22.79661;22.04988;-36.03566;,
 -22.79661;22.04988;9.64267;,
 -22.79661;9.82396;-36.03566;,
 -22.79661;9.82396;11.59921;,
 -18.20513;1.28483;-31.44416;,
 -18.20513;1.28483;7.00771;,
 -18.20513;31.75846;-31.44416;,
 18.29023;31.75846;-31.44416;,
 18.29023;30.68478;-31.44416;,
 -18.20513;30.68478;-31.44416;,
 18.29023;31.75846;-31.44416;,
 18.29023;31.75846;5.05120;,
 18.29023;30.68478;5.05120;,
 18.29023;30.68478;-31.44416;,
 -18.20513;31.75846;5.05120;,
 -18.20513;31.75846;-31.44416;,
 -18.20513;30.68478;-31.44416;,
 -18.20513;30.68478;5.05120;,
 -18.20513;1.27774;-31.44416;,
 18.29023;1.27774;-31.44416;,
 18.29023;0.20407;-31.44416;,
 -18.20513;0.20407;-31.44416;,
 18.29023;1.27774;-31.44416;,
 18.29023;1.27774;13.12842;,
 18.29023;0.20407;13.12842;,
 18.29023;0.20407;-31.44416;,
 -18.20513;1.27774;13.12842;,
 -18.20513;1.27774;-31.44416;,
 -18.20513;0.20407;-31.44416;,
 -18.20513;0.20407;13.12842;,
 -22.91084;18.81655;-36.07544;,
 -7.60857;10.71349;-36.07544;,
 -7.60857;9.72820;-36.07544;,
 -22.91084;13.04653;-36.07544;,
 7.69368;10.71349;-36.07544;,
 7.69368;9.72820;-36.07544;,
 22.99596;18.81655;-36.07544;,
 22.99596;13.04653;-36.07544;,
 22.89722;12.96100;9.87196;,
 22.89722;21.10812;-5.43038;,
 22.89719;22.09336;-5.43032;,
 22.89719;18.77508;9.87190;,
 22.89719;21.10807;-20.73260;,
 22.89719;12.96100;-36.03485;,
 22.89719;18.77508;-36.03488;,
 22.89719;22.09337;-20.73258;,
 -22.89099;12.96100;-36.03488;,
 -22.89099;21.10812;-20.73258;,
 -22.89098;22.09336;-20.73260;,
 -22.89099;18.77508;-36.03485;,
 -22.89099;21.10807;-5.43031;,
 -22.89098;12.96100;9.87190;,
 -22.89099;18.77508;9.87195;,
 -22.89098;22.09337;-5.43032;,
 0.15778;142.62149;-68.48344;,
 4.95766;137.93247;-54.97328;,
 15.99120;41.84681;36.94450;,
 0.51756;16.54495;-1.28241;,
 4.95766;137.93247;-54.97328;,
 -4.87254;137.93247;-54.97328;,
 -15.90610;41.84681;36.94450;,
 15.99120;41.84681;36.94450;,
 -4.87254;137.93247;-54.97328;,
 0.11397;142.62149;-68.48344;,
 0.33697;16.54495;-1.28241;,
 -15.90610;41.84681;36.94450;,
 -18.11429;23.62905;-5.17776;,
 18.19941;23.62905;-5.17776;,
 26.96780;-59.10373;38.92206;,
 -26.88270;-59.10373;38.92206;,
 18.19941;23.62905;-5.17776;,
 27.10240;36.14346;28.58136;,
 40.17027;-34.33630;76.34157;,
 26.96780;-59.10373;38.92206;,
 27.10240;36.14346;28.58136;,
 -27.01730;36.14346;28.58136;,
 -40.08516;-34.33630;76.34157;,
 40.17027;-34.33630;76.34157;,
 -27.01730;36.14346;28.58136;,
 -18.11429;23.62905;-5.17776;,
 -26.88270;-59.10373;38.92206;,
 -40.08516;-34.33630;76.34157;,
 18.19941;23.62905;-5.17776;,
 -18.11429;23.62905;-5.17776;,
 -26.88270;-59.10373;38.92206;,
 26.96780;-59.10373;38.92206;,
 7.66591;-7.92074;23.27544;,
 7.66591;-0.49202;34.49904;,
 7.66591;-55.31099;70.78291;,
 7.66591;-62.73980;59.55934;,
 7.66591;-0.49202;34.49904;,
 -7.58081;-0.49202;34.49904;,
 -7.58081;-55.31099;70.78291;,
 7.66591;-55.31099;70.78291;,
 -7.58081;-0.49202;34.49904;,
 -7.58081;-7.92074;23.27544;,
 -7.58081;-62.73980;59.55934;,
 -7.58081;-55.31099;70.78291;,
 7.44114;-55.00718;70.32832;,
 -7.35603;-55.00718;70.32832;,
 -7.35603;-62.21686;59.43563;,
 7.44114;-62.21686;59.43563;,
 25.02074;-15.91586;28.56729;,
 29.87546;-8.48714;39.79088;,
 34.06894;-62.08363;78.08095;,
 34.06894;-72.10382;62.94199;,
 29.87546;-8.48714;39.79088;,
 16.16281;-8.48714;39.79088;,
 13.50343;-62.08363;78.08095;,
 34.06894;-62.08363;78.08095;,
 16.16281;-8.48714;39.79088;,
 16.16281;-15.91586;28.56729;,
 13.50343;-72.10382;62.94199;,
 13.50343;-62.08363;78.08095;,
 33.76580;-61.67395;77.46782;,
 13.80657;-61.67395;77.46782;,
 13.80657;-71.39875;62.77526;,
 33.76580;-71.39875;62.77526;,
 -16.08936;-15.91586;28.56729;,
 -16.08936;-8.48714;39.79088;,
 -13.42995;-62.08363;78.08095;,
 -13.42995;-72.10382;62.94199;,
 -16.08936;-8.48714;39.79088;,
 -28.33256;-8.48714;39.79088;,
 -33.99545;-62.08363;78.08095;,
 -13.42995;-62.08363;78.08095;,
 -28.33256;-8.48714;39.79088;,
 -24.11825;-15.91586;28.56729;,
 -33.99545;-72.10382;62.94199;,
 -33.99545;-62.08363;78.08095;,
 -13.73312;-61.67395;77.46782;,
 -33.69226;-61.67395;77.46782;,
 -33.69226;-71.39875;62.77526;,
 -13.73312;-71.39875;62.77526;,
 13.91160;44.68662;24.69172;,
 4.14309;44.68662;24.69172;,
 2.24862;40.48903;44.20771;,
 16.89892;40.48903;44.20771;,
 16.68297;40.32954;43.98390;,
 2.46457;40.32954;43.98390;,
 2.46457;26.73189;42.15661;,
 16.68297;26.73189;42.15661;,
 -4.93145;44.68662;24.69172;,
 -14.69995;44.68662;24.69172;,
 -16.59444;40.48903;44.20771;,
 -1.94412;40.48903;44.20771;,
 -2.16008;40.32954;43.98390;,
 -16.37846;40.32954;43.98390;,
 -16.37846;26.73189;42.15661;,
 -2.16008;26.73189;42.15661;,
 -17.62029;35.97632;63.75762;,
 -14.43768;50.09823;28.12189;,
 -17.21221;42.48187;16.61494;,
 -25.04837;8.36882;47.42389;,
 -17.59612;35.97632;63.75762;,
 -25.02422;8.36882;47.42389;,
 -17.18804;42.48187;16.61494;,
 -14.41352;50.09823;28.12189;,
 17.70540;35.97632;63.75762;,
 25.13347;8.36882;47.42389;,
 17.29731;42.48187;16.61494;,
 14.52279;50.09823;28.12189;,
 17.68122;35.97632;63.75762;,
 14.49862;50.09823;28.12189;,
 17.27314;42.48187;16.61494;,
 25.10934;8.36882;47.42389;,
 6.13216;-0.23870;39.19347;,
 6.13216;7.03256;47.16609;,
 6.13216;-33.19739;80.73270;,
 6.13216;-40.46863;72.76005;,
 6.13216;7.03256;47.16609;,
 -6.04938;7.03256;47.16609;,
 -6.04938;-33.19739;80.73270;,
 6.13216;-33.19739;80.73270;,
 -6.04938;7.03256;47.16609;,
 -6.04938;-0.23870;39.19347;,
 -6.04938;-40.46863;72.76005;,
 -6.04938;-33.19739;80.73270;,
 5.95258;-33.00312;80.35007;,
 -5.86982;-33.00312;80.35007;,
 -5.86982;-40.05998;72.61250;,
 5.95258;-40.05998;72.61250;,
 19.99803;-6.10605;44.08897;,
 23.87679;1.16520;52.06162;,
 27.22723;-37.85025;87.06371;,
 27.22723;-47.65806;76.30986;,
 23.87679;1.16520;52.06162;,
 12.92092;1.16520;52.06162;,
 10.79614;-37.85025;87.06371;,
 27.22723;-37.85025;87.06371;,
 12.92092;1.16520;52.06162;,
 12.92092;-6.10605;44.08897;,
 10.79614;-47.65806;76.30986;,
 10.79614;-37.85025;87.06371;,
 26.98503;-37.58810;86.54757;,
 11.03835;-37.58810;86.54757;,
 11.03835;-47.10673;76.11076;,
 26.98503;-47.10673;76.11076;,
 -12.84740;-6.10605;44.08897;,
 -12.84740;1.16520;52.06162;,
 -10.72266;-37.85025;87.06371;,
 -10.72266;-47.65806;76.30986;,
 -12.84740;1.16520;52.06162;,
 -22.62930;1.16520;52.06162;,
 -27.15371;-37.85025;87.06371;,
 -10.72266;-37.85025;87.06371;,
 -22.62930;1.16520;52.06162;,
 -19.26219;-6.10605;44.08897;,
 -27.15371;-47.65806;76.30986;,
 -27.15371;-37.85025;87.06371;,
 -10.96487;-37.58810;86.54757;,
 -26.91152;-37.58810;86.54757;,
 -26.91152;-47.10673;76.11076;,
 -10.96487;-47.10673;76.11076;,
 4.08882;96.92850;-30.84251;,
 0.10110;103.01375;-21.64882;,
 0.10110;71.00269;27.53250;,
 6.28714;48.99525;28.87779;,
 0.09132;103.01375;-21.64882;,
 -4.00371;96.92850;-30.84251;,
 -6.20202;48.99525;28.87779;,
 0.09132;71.00269;27.53250;,
 1.44813;49.29375;85.26665;,
 -1.36302;49.29375;85.26665;,
 -6.20202;48.99525;28.87779;,
 6.28714;48.99525;28.87779;,
 0.05574;54.24738;84.96387;,
 0.05353;54.24738;84.96387;,
 7.16338;87.97094;-15.98937;,
 2.28678;94.22478;-14.62484;,
 10.18528;71.69355;17.84135;,
 12.03946;53.71867;22.92559;,
 2.28678;94.22478;-14.62484;,
 1.04460;94.26717;-14.56093;,
 8.32236;71.75698;17.93725;,
 10.18528;71.69355;17.84135;,
 1.04460;94.26717;-14.56093;,
 4.22953;88.08425;-15.81828;,
 4.32100;53.98168;23.32286;,
 8.32236;71.75698;17.93725;,
 10.12827;71.83421;17.30295;,
 8.32026;71.89581;17.39599;,
 4.43689;54.48597;23.01245;,
 11.92780;54.23072;22.62686;,
 -7.07826;87.97094;-15.98937;,
 -11.95436;53.71867;22.92559;,
 -10.10018;71.69355;17.84135;,
 -2.20166;94.22478;-14.62484;,
 -2.20166;94.22478;-14.62484;,
 -10.10018;71.69355;17.84135;,
 -8.23724;71.75698;17.93725;,
 -0.95948;94.26717;-14.56093;,
 -0.95948;94.26717;-14.56093;,
 -8.23724;71.75698;17.93725;,
 -4.23588;53.98168;23.32286;,
 -4.14443;88.08425;-15.81828;,
 -10.04316;71.83421;17.30295;,
 -11.84269;54.23072;22.62686;,
 -4.35179;54.48597;23.01245;,
 -8.23515;71.89581;17.39599;,
 -50.36480;54.47722;0.52537;,
 50.56010;54.47722;0.52537;,
 50.56010;23.94463;-3.68784;,
 -50.36480;23.94463;-3.68784;,
 50.56010;54.47722;0.52537;,
 50.56010;51.09382;28.74274;,
 50.56010;31.32313;32.64586;,
 50.56010;23.94463;-3.68784;,
 50.56010;51.09382;28.74274;,
 -50.36480;51.09382;28.74274;,
 -50.36480;31.32313;32.64586;,
 50.56010;31.32313;32.64586;,
 -50.36480;51.09382;28.74274;,
 -50.36480;54.47722;0.52537;,
 -50.36480;23.94463;-3.68784;,
 -50.36480;31.32313;32.64586;,
 50.56010;54.47722;0.52537;,
 -50.36480;54.47722;0.52537;,
 17.74990;79.09482;-25.57019;,
 27.05533;79.09482;-25.57019;,
 27.05533;34.09482;-25.57019;,
 17.74990;34.09482;-25.57019;,
 27.05533;79.09482;-25.57019;,
 27.05533;52.95001;8.79227;,
 27.05533;34.09482;8.79227;,
 27.05533;34.09482;-25.57019;,
 17.74990;52.95001;8.79227;,
 17.74990;79.09482;-25.57019;,
 17.74990;34.09482;-25.57019;,
 17.74990;34.09482;8.79227;,
 27.05533;79.09482;-25.57019;,
 17.74990;79.09482;-25.57019;,
 17.74990;34.09482;-25.57019;,
 27.05533;34.09482;-25.57019;,
 19.21780;76.33746;-25.61697;,
 25.58746;76.33746;-25.61697;,
 25.58746;69.96782;-25.61697;,
 19.21780;69.96782;-25.61697;,
 19.21780;36.85216;-25.61697;,
 19.21780;43.22184;-25.61697;,
 25.58746;43.22184;-25.61697;,
 25.58746;36.85216;-25.61697;,
 -17.66478;79.09482;-25.57019;,
 -17.66478;34.09482;-25.57019;,
 -26.97023;34.09482;-25.57019;,
 -26.97023;79.09482;-25.57019;,
 -26.97023;79.09482;-25.57019;,
 -26.97023;34.09482;-25.57019;,
 -26.97023;34.09482;8.79227;,
 -26.97023;52.95001;8.79227;,
 -17.66478;52.95001;8.79227;,
 -17.66478;34.09482;8.79227;,
 -17.66478;34.09482;-25.57019;,
 -17.66478;79.09482;-25.57019;,
 -17.66478;79.09482;-25.57019;,
 -26.97023;79.09482;-25.57019;,
 -17.66478;34.09482;-25.57019;,
 -26.97023;34.09482;-25.57019;,
 -19.13268;76.33746;-25.61697;,
 -19.13268;69.96782;-25.61697;,
 -25.50234;69.96782;-25.61697;,
 -25.50234;76.33746;-25.61697;,
 -19.13268;36.85216;-25.61697;,
 -25.50234;36.85216;-25.61697;,
 -25.50234;43.22184;-25.61697;,
 -19.13268;43.22184;-25.61697;,
 19.21780;65.35722;-25.61697;,
 25.58746;65.35722;-25.61697;,
 25.58746;58.98756;-25.61697;,
 19.21780;58.98756;-25.61697;,
 -19.13268;65.35722;-25.61697;,
 -19.13268;58.98756;-25.61697;,
 -25.50234;58.98756;-25.61697;,
 -25.50234;65.35722;-25.61697;,
 19.21780;54.48095;-25.61697;,
 25.58746;54.48095;-25.61697;,
 25.58746;48.11126;-25.61697;,
 19.21780;48.11126;-25.61697;,
 -19.13268;54.48095;-25.61697;,
 -19.13268;48.11126;-25.61697;,
 -25.50234;48.11126;-25.61697;,
 -25.50234;54.48095;-25.61697;,
 31.07120;69.19493;-24.09443;,
 52.19919;69.19493;-24.09443;,
 52.19919;26.88538;-24.09443;,
 31.07120;26.88538;-24.09443;,
 52.19919;69.19493;-24.09443;,
 44.29064;71.88533;48.90516;,
 44.29064;44.53418;48.90516;,
 52.19919;26.88538;-24.09443;,
 44.29064;71.88533;48.90516;,
 31.84399;71.88533;48.90516;,
 31.84399;44.53418;48.90516;,
 44.29064;44.53418;48.90516;,
 31.84399;71.88533;48.90516;,
 31.07120;69.19493;-24.09443;,
 31.07120;26.88538;-24.09443;,
 31.84399;44.53418;48.90516;,
 52.19919;69.19493;-24.09443;,
 31.07120;69.19493;-24.09443;,
 -30.98611;69.19493;-24.09443;,
 -30.98611;26.88538;-24.09443;,
 -52.11408;26.88538;-24.09443;,
 -52.11408;69.19493;-24.09443;,
 -52.11408;69.19493;-24.09443;,
 -52.11408;26.88538;-24.09443;,
 -44.20555;44.53418;48.90516;,
 -44.20555;71.88533;48.90516;,
 -44.20555;71.88533;48.90516;,
 -44.20555;44.53418;48.90516;,
 -31.75887;44.53418;48.90516;,
 -31.75887;71.88533;48.90516;,
 -31.75887;71.88533;48.90516;,
 -31.75887;44.53418;48.90516;,
 -30.98611;26.88538;-24.09443;,
 -30.98611;69.19493;-24.09443;,
 -30.98611;69.19493;-24.09443;,
 -52.11408;69.19493;-24.09443;,
 32.38090;67.33476;-24.10515;,
 38.75056;67.33476;-24.10515;,
 38.75056;60.96516;-24.10515;,
 32.38090;60.96516;-24.10515;,
 -32.29580;67.33476;-24.10515;,
 -32.29580;60.96516;-24.10515;,
 -38.66546;60.96516;-24.10515;,
 -38.66546;67.33476;-24.10515;,
 32.38090;56.40021;-24.10515;,
 38.75056;56.40021;-24.10515;,
 38.75056;50.03056;-24.10515;,
 32.38090;50.03056;-24.10515;,
 -32.29580;56.40021;-24.10515;,
 -32.29580;50.03056;-24.10515;,
 -38.66546;50.03056;-24.10515;,
 -38.66546;56.40021;-24.10515;,
 32.38090;45.44214;-24.10515;,
 38.75056;45.44214;-24.10515;,
 38.75056;39.07250;-24.10515;,
 32.38090;39.07250;-24.10515;,
 -32.29580;45.44214;-24.10515;,
 -32.29580;39.07250;-24.10515;,
 -38.66546;39.07250;-24.10515;,
 -38.66546;45.44214;-24.10515;,
 32.38090;34.49799;-24.10515;,
 38.75056;34.49799;-24.10515;,
 38.75056;28.12832;-24.10515;,
 32.38090;28.12832;-24.10515;,
 -32.29580;34.49799;-24.10515;,
 -32.29580;28.12832;-24.10515;,
 -38.66546;28.12832;-24.10515;,
 -38.66546;34.49799;-24.10515;,
 44.17603;67.33476;-24.10515;,
 50.54569;67.33476;-24.10515;,
 50.54569;60.96516;-24.10515;,
 44.17603;60.96516;-24.10515;,
 -44.09093;67.33476;-24.10515;,
 -44.09093;60.96516;-24.10515;,
 -50.46058;60.96516;-24.10515;,
 -50.46058;67.33476;-24.10515;,
 44.17603;56.32518;-24.10515;,
 50.54569;56.32518;-24.10515;,
 50.54569;49.95550;-24.10515;,
 44.17603;49.95550;-24.10515;,
 -44.09093;56.32518;-24.10515;,
 -44.09093;49.95550;-24.10515;,
 -50.46058;49.95550;-24.10515;,
 -50.46058;56.32518;-24.10515;,
 44.17603;45.39137;-24.10515;,
 50.54569;45.39137;-24.10515;,
 50.54569;39.02172;-24.10515;,
 44.17603;39.02172;-24.10515;,
 -44.09093;45.39137;-24.10515;,
 -44.09093;39.02172;-24.10515;,
 -50.46058;39.02172;-24.10515;,
 -50.46058;45.39137;-24.10515;,
 44.17603;34.41826;-24.10515;,
 50.54569;34.41826;-24.10515;,
 50.54569;28.04861;-24.10515;,
 44.17603;28.04861;-24.10515;,
 -44.09093;34.41826;-24.10515;,
 -44.09093;28.04861;-24.10515;,
 -50.46058;28.04861;-24.10515;,
 -50.46058;34.41826;-24.10515;,
 -56.32620;33.15936;31.63804;,
 -56.32620;57.89282;31.63804;,
 -50.80508;57.89282;-13.36199;,
 -50.80508;33.15936;-13.36199;,
 56.41130;33.15936;31.63804;,
 50.89020;33.15936;-13.36199;,
 50.89020;57.89282;-13.36199;,
 56.41130;57.89282;31.63804;,
 -56.32623;57.89282;31.63804;,
 -56.32623;33.15936;31.63804;,
 -50.80508;33.15936;-13.36199;,
 -50.80508;57.89282;-13.36199;,
 56.41132;57.89282;31.63804;,
 50.89020;57.89282;-13.36199;,
 50.89020;33.15936;-13.36199;,
 56.41132;33.15936;31.63804;;
 
 138;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;8,5,12,13;,
 4;14,15,16,17;,
 4;18,19,20,21;,
 4;18,15,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;31,30,32,33;,
 4;33,32,34,35;,
 4;36,37,38,39;,
 4;39,38,40,41;,
 4;41,40,42,43;,
 4;44,45,46,47;,
 4;47,46,48,49;,
 4;49,48,50,51;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;77,80,81,78;,
 4;80,82,83,81;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;96,97,98,99;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;116,117,118,119;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;124,117,128,129;,
 4;130,131,118,127;,
 4;132,133,134,135;,
 4;136,137,138,139;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;156,157,158,159;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;176,177,178,179;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,190,191;,
 4;192,193,194,195;,
 4;196,197,198,199;,
 4;200,201,202,203;,
 4;204,205,206,207;,
 4;208,209,210,211;,
 4;212,213,214,215;,
 4;216,217,218,219;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;228,229,230,231;,
 4;232,233,234,235;,
 4;236,237,238,239;,
 4;240,241,242,243;,
 4;244,245,246,247;,
 4;248,249,250,251;,
 4;252,253,254,255;,
 4;256,257,258,259;,
 4;260,261,262,263;,
 4;264,265,266,267;,
 4;268,269,270,271;,
 4;272,268,271,262;,
 4;273,272,262,267;,
 4;269,273,267,270;,
 4;274,275,276,277;,
 4;278,279,280,281;,
 4;282,283,284,285;,
 4;286,287,288,289;,
 4;290,291,292,293;,
 4;294,295,296,297;,
 4;298,299,300,301;,
 4;302,303,304,305;,
 4;306,307,308,309;,
 4;310,311,312,313;,
 4;314,315,316,317;,
 4;318,319,320,321;,
 4;318,311,322,323;,
 4;324,325,326,327;,
 4;328,329,330,331;,
 4;332,333,334,335;,
 4;332,329,336,337;,
 4;338,339,330,335;,
 4;340,341,342,343;,
 4;344,345,346,347;,
 4;348,349,350,351;,
 4;352,353,354,355;,
 4;356,357,358,359;,
 4;356,360,361,355;,
 4;362,357,354,363;,
 4;364,365,366,367;,
 4;368,369,370,371;,
 4;372,373,374,375;,
 4;376,377,378,379;,
 4;380,381,382,383;,
 4;384,385,386,387;,
 4;388,389,390,391;,
 4;392,393,394,395;,
 4;396,397,398,399;,
 4;400,401,402,403;,
 4;400,393,404,405;,
 4;406,407,408,409;,
 4;410,411,412,413;,
 4;414,415,416,417;,
 4;418,419,420,421;,
 4;418,422,423,413;,
 4;424,425,426,427;,
 4;428,429,430,431;,
 4;432,433,434,435;,
 4;436,437,438,439;,
 4;440,441,442,443;,
 4;444,445,446,447;,
 4;448,449,450,451;,
 4;452,453,454,455;,
 4;456,457,458,459;,
 4;460,461,462,463;,
 4;464,465,466,467;,
 4;468,469,470,471;,
 4;472,473,474,475;,
 4;476,477,478,479;,
 4;480,481,482,483;,
 4;484,485,486,487;,
 4;488,489,490,491;,
 4;492,493,494,495;,
 4;496,497,498,499;,
 4;500,501,502,503;;
 
 MeshMaterialList {
  3;
  138;
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  1,
  2,
  2,
  2,
  1,
  2,
  2,
  2,
  1,
  2,
  1,
  2,
  1,
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  1,
  2,
  2,
  2,
  1,
  2,
  2,
  2,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  1,
  2,
  2,
  2,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2;;
  Material {
   0.023550;0.117000;0.004650;1.000000;;
   0.000000;
   0.060000;0.060000;0.060000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.012800;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;0.016000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   0.000000;
   0.060000;0.060000;0.060000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  92;
  0.000000;0.888050;-0.459746;,
  0.000000;0.577267;-0.816556;,
  0.459747;0.888050;0.000000;,
  0.816556;0.577266;0.000000;,
  -0.459747;0.888050;0.000000;,
  -0.816556;0.577266;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.473579;-0.880751;,
  0.000000;0.244181;-0.969730;,
  0.000000;-0.244182;-0.969729;,
  0.000000;-0.473581;-0.880751;,
  0.880752;0.473578;0.000000;,
  0.969730;0.244181;0.000000;,
  0.969730;-0.244181;-0.000000;,
  0.880751;-0.473580;-0.000000;,
  -0.880752;0.473578;0.000000;,
  -0.969730;0.244180;0.000000;,
  -0.969730;-0.244181;0.000000;,
  -0.880751;-0.473579;0.000000;,
  1.000000;0.000018;0.000005;,
  -1.000000;0.000007;-0.000003;,
  -1.000000;0.000006;0.000001;,
  -0.917833;-0.192858;-0.346969;,
  0.924372;-0.182088;-0.335231;,
  0.000000;0.691261;0.722605;,
  0.000000;-0.470386;-0.882461;,
  0.959879;-0.031606;-0.278626;,
  0.000000;0.560976;0.827832;,
  0.000000;0.551937;0.833886;,
  0.000000;-0.833887;0.551935;,
  -0.999185;0.033661;-0.022280;,
  0.979896;-0.007954;-0.199349;,
  0.000000;0.581307;0.813684;,
  0.000000;-0.833886;0.551937;,
  -0.981423;0.017846;-0.191023;,
  0.999185;0.033662;-0.022280;,
  0.000000;0.581307;0.813684;,
  0.000000;-0.833886;0.551937;,
  0.000000;0.977642;0.210275;,
  0.000000;-0.133185;0.991091;,
  -0.964792;0.260861;0.033596;,
  0.964791;-0.260861;-0.033596;,
  0.964792;0.260861;0.033596;,
  -0.964791;-0.260862;-0.033596;,
  0.000000;0.640653;0.767830;,
  0.000000;-0.738860;0.673859;,
  -0.999179;0.029928;-0.027295;,
  0.979976;-0.040697;-0.194913;,
  0.000000;0.667785;0.744354;,
  0.000000;-0.738860;0.673858;,
  -0.981580;-0.013936;-0.190543;,
  0.999179;0.029927;-0.027294;,
  0.000000;0.667785;0.744354;,
  0.000000;-0.738860;0.673859;,
  -0.933984;0.297635;0.197707;,
  -0.947229;0.288645;0.139434;,
  0.936629;0.291940;0.193641;,
  0.949044;0.283594;0.137443;,
  0.000000;-0.999986;0.005293;,
  0.958249;0.274289;0.080780;,
  0.000000;0.959980;0.280069;,
  -0.993244;-0.084468;0.079574;,
  0.934298;0.346620;0.083318;,
  0.056990;0.826650;0.559823;,
  0.059126;0.294515;0.953816;,
  0.993244;-0.084468;0.079573;,
  -0.934298;0.346620;0.083318;,
  -0.056990;0.826650;0.559824;,
  -0.059126;0.294513;0.953817;,
  0.000000;0.136695;-0.990613;,
  0.000000;0.193681;0.981064;,
  0.994183;0.000000;0.107707;,
  0.000000;0.000000;1.000000;,
  -0.994183;0.000000;0.107706;,
  -0.992557;0.000000;-0.121778;,
  0.992557;0.000000;-0.121778;,
  0.992557;0.000000;0.121779;,
  -0.992557;0.000000;0.121778;,
  0.000000;1.000000;0.000000;,
  -0.959879;-0.031606;-0.278626;,
  0.000000;0.937649;-0.347584;,
  0.000000;-0.833886;0.551937;,
  -0.957015;0.278601;0.080651;,
  0.000000;0.992888;0.119052;,
  0.000000;0.795835;0.605514;,
  0.000000;-1.000000;-0.000000;,
  -0.999944;0.000000;0.010586;,
  0.000000;0.999322;-0.036830;,
  0.999944;0.000000;0.010585;,
  0.000000;0.999322;-0.036830;;
  138;
  4;0,0,1,1;,
  4;3,2,3,3;,
  4;4,5,5,5;,
  4;4,2,0,0;,
  4;7,7,7,7;,
  4;6,6,6,6;,
  4;80,80,80,80;,
  4;8,8,8,8;,
  4;9,9,10,10;,
  4;10,10,11,11;,
  4;11,11,12,12;,
  4;13,13,14,14;,
  4;14,14,15,15;,
  4;15,15,16,16;,
  4;17,17,18,18;,
  4;18,18,19,19;,
  4;19,19,20,20;,
  4;8,8,8,8;,
  4;7,7,7,7;,
  4;6,6,6,6;,
  4;8,8,8,8;,
  4;7,7,7,7;,
  4;6,6,6,6;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;21,21,21,21;,
  4;7,7,7,7;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;24,24,24,24;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;81,81,81,81;,
  4;82,82,82,82;,
  4;83,83,83,83;,
  4;7,7,7,7;,
  4;30,30,30,30;,
  4;6,6,6,6;,
  4;31,31,31,31;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;32,32,32,32;,
  4;35,35,35,35;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;36,36,36,36;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;44,44,44,44;,
  4;45,45,45,45;,
  4;7,7,7,7;,
  4;46,46,46,46;,
  4;6,6,6,6;,
  4;47,47,47,47;,
  4;49,49,49,49;,
  4;50,50,50,50;,
  4;48,48,48,48;,
  4;51,51,51,51;,
  4;53,53,53,53;,
  4;54,54,54,54;,
  4;52,52,52,52;,
  4;55,55,55,55;,
  4;58,58,59,59;,
  4;56,56,57,57;,
  4;60,60,60,60;,
  4;61,61,59,59;,
  4;62,62,62,62;,
  4;84,84,57,57;,
  4;64,64,64,64;,
  4;65,65,65,65;,
  4;63,63,63,63;,
  4;66,66,66,66;,
  4;68,68,68,68;,
  4;69,69,69,69;,
  4;67,67,67,67;,
  4;70,70,70,70;,
  4;71,71,71,71;,
  4;7,7,7,7;,
  4;72,72,72,72;,
  4;6,6,6,6;,
  4;85,85,85,85;,
  4;8,8,8,8;,
  4;7,7,7,7;,
  4;6,6,6,6;,
  4;86,86,86,86;,
  4;87,87,87,87;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;86,86,86,86;,
  4;87,87,87,87;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;73,73,73,73;,
  4;74,74,74,74;,
  4;88,88,88,88;,
  4;89,89,89,89;,
  4;8,8,8,8;,
  4;75,75,75,75;,
  4;74,74,74,74;,
  4;90,90,90,90;,
  4;91,91,91,91;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;78,78,78,78;,
  4;79,79,79,79;;
 }
 MeshTextureCoords {
  504;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.000000;0.333330;,
  1.000000;0.666670;,
  0.000000;0.666670;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.000000;0.333330;,
  1.000000;0.666670;,
  0.000000;0.666670;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.000000;0.333330;,
  1.000000;0.666670;,
  0.000000;0.666670;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.666670;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.666670;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;;
 }
}
