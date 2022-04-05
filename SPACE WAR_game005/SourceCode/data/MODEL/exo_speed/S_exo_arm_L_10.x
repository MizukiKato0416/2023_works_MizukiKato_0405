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
 224;
 4.19424;3.14234;-1.14819;,
 13.60372;2.19181;-1.34304;,
 13.56512;0.98527;-1.41973;,
 3.50983;1.49336;-1.30953;,
 13.56510;-0.05503;-1.14819;,
 6.92989;0.01687;-1.14819;,
 13.60372;2.19181;-1.34304;,
 13.60372;2.19181;1.37718;,
 13.56512;0.98527;1.45389;,
 13.56512;0.98527;-1.41973;,
 13.60372;2.19181;1.37718;,
 4.19424;3.14234;1.18235;,
 3.50983;1.49336;1.34369;,
 13.56512;0.98527;1.45389;,
 6.92989;0.01687;1.18235;,
 13.56510;-0.05503;1.18235;,
 4.19424;3.14234;1.18235;,
 4.19424;3.14234;-1.14819;,
 3.50983;1.49336;-1.30953;,
 3.50983;1.49336;1.34369;,
 13.60372;2.19181;-1.34304;,
 4.19424;3.14234;-1.14819;,
 -2.32284;-0.03770;-2.47932;,
 9.98088;-0.03771;-1.32977;,
 7.70419;-2.25485;-2.13765;,
 -2.32284;-2.25485;-2.47932;,
 9.98088;-0.03771;1.44526;,
 -3.13946;-0.03771;2.20531;,
 -3.13946;-2.25485;2.20531;,
 7.70419;-2.25485;2.25317;,
 -3.13946;-0.03771;2.20531;,
 -2.32284;-0.03770;-2.47932;,
 -2.32284;-2.25485;-2.47932;,
 -3.13946;-2.25485;2.20531;,
 9.98088;-0.03771;1.44526;,
 9.98088;-0.03771;-1.32977;,
 -2.32284;-0.03770;-2.47932;,
 -2.32284;-2.25485;-2.47932;,
 7.70419;-2.25485;-2.13765;,
 7.70419;-2.25485;2.25317;,
 13.71470;1.06068;-1.92911;,
 16.63165;0.81339;-1.55126;,
 16.63165;-1.25422;-1.55126;,
 13.71471;-1.50154;-1.92911;,
 16.63165;0.81339;-1.55126;,
 16.63165;0.81339;1.60801;,
 16.63165;-1.25422;1.60801;,
 16.63165;-1.25422;-1.55126;,
 16.63165;0.81339;1.60801;,
 13.71470;1.06068;1.98584;,
 13.71471;-1.50154;1.98584;,
 16.63165;-1.25422;1.60801;,
 13.71470;1.06068;1.98584;,
 16.63165;0.81339;-1.55126;,
 13.71470;1.06068;-1.92911;,
 13.71471;-1.50154;-1.92911;,
 16.63165;-1.25422;-1.55126;,
 13.71471;-1.50154;1.98584;,
 10.26238;2.86029;2.02579;,
 10.93551;2.86029;2.02579;,
 10.93551;2.86029;-2.18037;,
 10.26238;2.86029;-2.18037;,
 10.25566;2.85604;-2.17910;,
 10.72748;2.43749;-2.17910;,
 7.10834;-1.11903;-1.79357;,
 6.63651;-0.63893;-1.79357;,
 10.91953;2.85605;-2.17910;,
 14.53866;-0.63892;-1.92681;,
 14.06686;-1.11904;-1.92681;,
 10.26279;2.85455;-2.17910;,
 10.92055;2.85606;2.03509;,
 10.27309;2.85676;2.03509;,
 14.12421;-1.11903;2.03509;,
 14.59602;-0.63892;2.03509;,
 10.25513;2.85605;2.03509;,
 6.57966;-0.63890;1.62402;,
 7.05148;-1.11903;1.62402;,
 10.67066;2.43747;2.03509;,
 10.64274;0.56968;1.21103;,
 7.70987;-2.25252;2.25214;,
 7.70987;-2.25252;-2.16065;,
 10.64274;0.56968;-1.11951;,
 8.04821;-1.69723;-1.76505;,
 14.77811;-1.41437;-1.76505;,
 14.77811;-1.41437;0.28295;,
 8.04821;-1.69723;0.28295;,
 14.83676;-0.21087;1.09156;,
 9.05329;0.52328;1.24987;,
 8.04823;-1.18756;-0.68005;,
 14.77810;-1.06696;-0.49947;,
 14.83676;-0.21087;-1.14104;,
 14.77810;-1.06696;-0.30451;,
 8.04823;-1.51092;-0.46084;,
 9.05329;0.52328;-1.13508;,
 16.65236;-1.51590;-1.01325;,
 16.65235;1.02088;-1.01325;,
 19.18913;1.02090;-1.01325;,
 19.18914;-1.51589;-1.01325;,
 16.65235;1.02088;-1.01325;,
 16.65236;-0.34825;1.10658;,
 19.18912;-0.34825;1.10658;,
 19.18913;1.02090;-1.01325;,
 16.65236;-0.28497;1.10658;,
 16.65236;-1.51590;-1.01325;,
 19.18914;-1.51589;-1.01325;,
 19.18913;-0.28497;1.10658;,
 18.17338;0.36210;-2.42861;,
 23.04906;0.36209;-2.01007;,
 22.71625;-0.55494;-2.01007;,
 18.17338;-0.55495;-2.42861;,
 18.17338;0.36210;2.39867;,
 19.22519;0.49460;-0.01496;,
 19.22521;-0.42244;-0.01496;,
 18.17338;-0.55495;2.39867;,
 21.98109;0.36209;2.39867;,
 23.04906;0.49458;-0.49079;,
 19.22519;0.49460;-0.01496;,
 23.04906;0.36209;-2.01007;,
 18.17338;0.36210;-2.42861;,
 19.22521;-0.42244;-0.01496;,
 22.63937;-0.42246;-0.49079;,
 21.64916;-0.55493;2.39867;,
 23.01330;0.15185;-1.76535;,
 25.15984;0.15184;-2.04958;,
 25.01927;-0.39054;-2.03326;,
 22.83310;-0.39056;-1.74903;,
 22.95083;0.18016;0.20534;,
 25.17114;0.16281;0.22168;,
 25.15984;0.15184;-2.04958;,
 23.01330;0.15185;-1.76535;,
 22.83310;-0.39056;-1.74903;,
 25.01927;-0.39054;-2.03326;,
 25.03057;-0.40329;0.22168;,
 22.77065;-0.38594;0.20534;,
 25.40142;0.15185;-2.10996;,
 26.77808;-0.94899;-2.23508;,
 26.47338;-1.12555;-2.21217;,
 25.33367;-0.30131;-2.15975;,
 25.33897;0.18018;0.15749;,
 26.78937;-0.93804;0.10010;,
 26.77808;-0.94899;-2.23508;,
 25.40142;0.15185;-2.10996;,
 25.33367;-0.30131;-2.15975;,
 26.47338;-1.12555;-2.21217;,
 26.48471;-1.13831;0.10010;,
 25.27121;-0.29671;0.15749;,
 26.90779;-1.03437;-2.24964;,
 27.70050;-2.16784;-1.82939;,
 27.39584;-2.34438;-1.81622;,
 26.84005;-1.48753;-2.30522;,
 27.70050;-2.16784;-1.82939;,
 27.71182;-2.15686;-0.75141;,
 27.40714;-2.35713;-0.75141;,
 27.39584;-2.34438;-1.81622;,
 26.84535;-1.00605;0.09922;,
 27.70050;-2.16784;-1.82939;,
 26.90779;-1.03437;-2.24964;,
 26.84005;-1.48753;-2.30522;,
 27.39584;-2.34438;-1.81622;,
 26.77758;-1.48293;0.09922;,
 22.61168;0.15185;0.55451;,
 24.73000;0.15184;1.00312;,
 24.59203;-0.39053;0.97157;,
 22.43640;-0.39053;0.50973;,
 21.89497;0.18017;2.39130;,
 23.98249;0.16280;3.14787;,
 24.73000;0.15184;1.00312;,
 22.61168;0.15185;0.55451;,
 22.43640;-0.39053;0.50973;,
 24.59203;-0.39053;0.97157;,
 23.84997;-0.40330;3.10094;,
 21.72512;-0.38593;2.33117;,
 24.97786;0.15185;1.02685;,
 26.37570;-0.94899;1.20353;,
 26.08086;-1.12556;1.12342;,
 24.93062;-0.30132;0.95729;,
 24.16210;0.18016;3.14336;,
 25.54846;-0.93803;3.57343;,
 26.37570;-0.94899;1.20353;,
 24.97786;0.15185;1.02685;,
 24.93062;-0.30132;0.95729;,
 26.08086;-1.12556;1.12342;,
 25.26129;-1.13831;3.47172;,
 24.09824;-0.29671;3.12074;,
 26.50507;-1.03436;1.22691;,
 27.22078;-2.16783;1.63244;,
 26.92503;-2.34438;1.58825;,
 26.45974;-1.48753;1.15191;,
 27.22078;-2.16783;1.63244;,
 26.53291;-2.15686;2.75728;,
 26.24571;-2.35713;2.69939;,
 26.92503;-2.34438;1.58825;,
 25.60153;-1.00604;3.59129;,
 27.22078;-2.16783;1.63244;,
 26.50507;-1.03436;1.22691;,
 26.45974;-1.48753;1.15191;,
 26.92503;-2.34438;1.58825;,
 25.53763;-1.48293;3.56867;,
 18.23627;-0.60572;-2.63719;,
 20.50938;-2.61727;-2.43398;,
 20.50945;-2.38913;-2.16477;,
 18.50369;-0.61247;-2.26186;,
 21.83559;-2.47463;-2.72601;,
 19.38804;-0.57556;-2.78239;,
 19.69881;-0.54925;-2.41533;,
 21.84051;-2.26337;-2.42888;,
 19.38804;-0.57556;-2.78239;,
 21.83559;-2.47463;-2.72601;,
 20.50938;-2.61727;-2.43398;,
 18.23627;-0.60572;-2.63719;,
 22.04772;-3.15869;-1.83370;,
 23.15288;-3.30298;-1.91804;,
 23.15781;-3.09171;-1.62093;,
 22.04921;-2.92869;-1.56582;,
 23.15288;-3.30298;-1.91804;,
 21.90928;-2.51907;-2.70716;,
 22.22005;-2.49277;-2.34010;,
 23.15781;-3.09171;-1.62093;,
 21.90928;-2.51907;-2.70716;,
 22.04772;-3.15869;-1.83370;,
 20.61831;-2.72993;-2.43116;,
 20.88268;-2.74067;-2.05296;,
 22.04921;-2.92869;-1.56582;,
 22.22005;-2.49277;-2.34010;;
 
 61;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;6,7,8,9;,
 4;10,11,12,13;,
 4;13,12,14,15;,
 4;16,17,18,19;,
 4;16,7,20,21;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;30,34,35,36;,
 4;37,38,39,33;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,45,53,54;,
 4;55,56,46,57;,
 4;58,59,60,61;,
 4;62,63,64,65;,
 4;66,67,68,69;,
 4;70,71,72,73;,
 4;74,75,76,77;,
 4;78,79,80,81;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;90,91,92,93;,
 4;94,95,96,97;,
 4;98,99,100,101;,
 4;102,103,104,105;,
 4;106,107,108,109;,
 4;110,111,112,113;,
 4;110,114,115,116;,
 4;116,115,117,118;,
 4;119,120,121,113;,
 4;122,123,124,125;,
 4;126,127,128,129;,
 4;130,131,132,133;,
 4;134,135,136,137;,
 4;138,139,140,141;,
 4;142,143,144,145;,
 4;146,147,148,149;,
 4;150,151,152,153;,
 4;154,151,155,156;,
 4;157,158,152,159;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;176,177,178,179;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,190,191;,
 4;192,189,193,194;,
 4;195,196,190,197;,
 4;198,199,200,201;,
 4;202,203,204,205;,
 4;206,207,208,209;,
 4;210,211,212,213;,
 4;214,215,216,217;,
 4;218,211,219,220;,
 4;221,222,212,223;;
 
 MeshMaterialList {
  5;
  61;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
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
  0,
  0,
  0,
  0,
  0,
  2,
  4,
  4,
  4,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.432800;0.432800;0.432800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.065600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.031200;0.031200;0.031200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.248000;0.248000;0.248000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.615200;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  64;
  -0.010038;0.081847;-0.996594;,
  -0.010429;-0.060656;-0.998104;,
  -0.010608;-0.201928;-0.979343;,
  0.999489;-0.031977;-0.000000;,
  -0.010607;-0.201928;0.979343;,
  -0.010036;0.081855;0.996594;,
  -0.010428;-0.060652;0.998105;,
  0.062522;0.130270;-0.989505;,
  0.025749;0.147276;0.988760;,
  0.128463;0.000000;-0.991714;,
  1.000000;0.000001;0.000000;,
  0.128456;0.000000;0.991715;,
  0.000000;1.000000;0.000000;,
  -0.052445;-0.055182;-0.997098;,
  0.017938;-0.049178;-0.998629;,
  0.000000;0.000000;1.000000;,
  -0.057467;-0.056759;0.996733;,
  0.693381;-0.720572;-0.000000;,
  0.041993;-0.999118;-0.000000;,
  -0.051654;-0.817285;0.573914;,
  -0.022983;-0.526587;-0.849810;,
  -0.923606;0.383343;0.000000;,
  0.100507;0.994936;0.000000;,
  -0.985144;-0.000000;-0.171728;,
  0.000000;1.000000;0.000001;,
  0.000000;-1.000000;0.000001;,
  0.084472;0.996426;0.000000;,
  0.084484;-0.996425;-0.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000003;0.840024;0.542549;,
  0.000002;-0.864778;0.502154;,
  0.088626;-0.015514;-0.995944;,
  0.000016;0.999947;-0.010272;,
  -0.003351;-0.998670;-0.051455;,
  0.002990;0.998673;0.051414;,
  -0.916734;-0.000014;-0.399499;,
  -0.130093;0.008593;-0.991465;,
  0.003641;0.999949;-0.009470;,
  -0.004210;-0.999990;-0.001768;,
  -0.032463;0.043739;-0.998515;,
  0.617473;0.786592;0.000121;,
  -0.578202;-0.815858;-0.007672;,
  0.357926;-0.187139;-0.914805;,
  0.525583;-0.850720;-0.006149;,
  0.813037;0.582212;-0.000112;,
  -0.830235;-0.557343;-0.008910;,
  0.208330;0.008616;-0.978021;,
  0.006597;0.999949;-0.007709;,
  -0.003382;-0.999990;-0.003080;,
  0.214597;0.109825;-0.970509;,
  0.581721;0.786771;0.206378;,
  -0.542565;-0.815806;-0.200209;,
  0.457592;-0.111223;-0.882178;,
  0.481733;-0.825526;0.294006;,
  0.769585;0.521486;0.368499;,
  -0.785152;-0.487175;-0.382358;,
  -0.599409;-0.640851;0.479603;,
  0.539367;0.678960;-0.498093;,
  -0.072083;-0.810123;-0.581812;,
  0.045585;0.866151;0.497699;,
  -0.070492;-0.785357;0.615016;,
  0.683496;0.520173;-0.512107;,
  -0.002959;0.997406;-0.071918;,
  -0.148402;-0.245001;-0.958098;;
  61;
  4;0,0,1,1;,
  4;1,1,2,2;,
  4;3,3,3,3;,
  4;5,5,6,6;,
  4;6,6,4,4;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;35,35,35,35;,
  4;34,34,32,32;,
  4;32,32,62,62;,
  4;33,33,33,33;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;44,44,44,44;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;47,47,47,47;,
  4;48,48,48,48;,
  4;49,49,49,49;,
  4;50,50,50,50;,
  4;51,51,51,51;,
  4;52,52,52,52;,
  4;53,53,53,53;,
  4;54,54,54,54;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;57,57,57,57;,
  4;63,63,63,63;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;58,58,58,58;,
  4;59,59,59,59;;
 }
 MeshTextureCoords {
  224;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
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
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
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
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
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
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
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
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
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
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
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
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;;
 }
}
