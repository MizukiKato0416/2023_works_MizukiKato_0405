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
 104;
 1.01400;-1.92314;-2.20213;,
 0.89646;-4.53637;-2.20213;,
 0.52453;-4.53637;-2.41855;,
 0.52453;-1.21737;-2.41855;,
 -0.55425;-4.53637;-2.41855;,
 -0.55425;-1.21737;-2.41855;,
 -1.55461;-4.53637;-2.20213;,
 -1.63302;-1.87248;-2.20213;,
 0.74010;-8.70554;-2.15955;,
 0.52453;-8.70554;-2.37599;,
 -0.55425;-8.70554;-2.37599;,
 -1.39798;-8.70554;-2.15955;,
 0.86417;-11.76266;-1.97691;,
 0.52453;-12.33522;-2.19334;,
 -0.55425;-12.33522;-2.19334;,
 -1.32038;-12.00187;-1.97691;,
 -1.63302;-1.87248;-2.20213;,
 -1.55461;-4.53637;-2.20213;,
 -2.13124;-4.53637;-0.72359;,
 -2.18267;-1.02228;-0.72359;,
 -2.13124;-4.53637;0.75495;,
 -2.18267;-1.02228;0.75495;,
 -1.55461;-4.53637;1.90292;,
 -1.63302;-2.29760;2.14933;,
 -1.39798;-8.70554;-2.15955;,
 -1.97731;-8.70554;-0.72359;,
 -1.97731;-8.70554;0.58593;,
 -1.39798;-8.70554;1.35925;,
 -1.32038;-12.00187;-1.97691;,
 -1.63023;-12.31662;-0.72359;,
 -1.63023;-12.31662;0.39683;,
 -1.39798;-11.71175;1.08491;,
 -1.63302;-2.29760;2.14933;,
 -1.55461;-4.53637;1.90292;,
 -0.55425;-4.53637;2.29879;,
 -0.55425;-1.77713;2.51057;,
 0.52453;-4.53637;2.29879;,
 0.52453;-1.77713;2.55202;,
 0.89646;-4.53637;1.90292;,
 1.01400;-2.34827;2.14933;,
 -1.39798;-8.70554;1.35925;,
 -0.55425;-8.70554;1.75510;,
 0.52453;-8.70554;1.75510;,
 0.74010;-8.70554;1.35925;,
 -1.39798;-11.71175;1.08491;,
 -0.55425;-11.71175;1.48077;,
 0.52453;-11.71175;1.48077;,
 0.74010;-11.71175;1.08491;,
 1.01400;-2.34827;2.14933;,
 0.89646;-4.53637;1.90292;,
 1.78140;-4.53637;1.03356;,
 1.62797;-1.21870;1.03356;,
 1.78140;-4.53637;-0.44497;,
 1.62797;-1.21870;-0.44497;,
 0.89646;-4.53637;-2.20213;,
 1.01400;-1.92314;-2.20213;,
 0.74010;-8.70554;1.35925;,
 1.58718;-8.70554;0.86454;,
 1.58718;-8.70554;-0.44497;,
 0.74010;-8.70554;-2.15955;,
 0.74010;-11.71175;1.08491;,
 0.96742;-12.56141;0.67544;,
 1.06406;-12.71286;-0.44497;,
 0.86417;-11.76266;-1.97691;,
 1.62797;-1.21870;1.03356;,
 0.52453;-0.36719;0.75495;,
 0.52453;-1.77713;2.55202;,
 -0.55425;-0.36719;0.75495;,
 -0.55425;-1.77713;2.51057;,
 -2.18267;-1.02228;0.75495;,
 1.62797;-1.21870;-0.44497;,
 0.52453;-0.36719;-0.72359;,
 -0.55425;-0.36719;-0.72359;,
 -2.18267;-1.02228;-0.72359;,
 1.01400;-1.92314;-2.20213;,
 0.52453;-1.21737;-2.41855;,
 -0.55425;-1.21737;-2.41855;,
 -1.63302;-1.87248;-2.20213;,
 0.96742;-12.56141;0.67544;,
 0.52453;-11.71175;1.48077;,
 0.52453;-13.02613;0.39683;,
 -0.55425;-11.71175;1.48077;,
 -0.55425;-13.02613;0.39683;,
 -1.63023;-12.31662;0.39683;,
 1.06406;-12.71286;-0.44497;,
 0.52453;-13.02613;-0.72359;,
 -0.55425;-13.02613;-0.72359;,
 -1.63023;-12.31662;-0.72359;,
 0.86417;-11.76266;-1.97691;,
 0.52453;-12.33522;-2.19334;,
 -0.55425;-12.33522;-2.19334;,
 -1.32038;-12.00187;-1.97691;,
 -0.00941;1.64549;-0.01621;,
 -1.63152;0.02337;-0.01621;,
 -0.00941;0.02337;1.60589;,
 -0.00941;1.64549;-0.01621;,
 1.61271;0.02337;-0.01621;,
 -0.00941;1.64549;-0.01621;,
 -0.00941;0.02337;-1.63833;,
 -0.00941;0.02337;-1.63833;,
 -0.00941;-1.59875;-0.01621;,
 -0.00941;-1.59875;-0.01621;,
 -0.00941;-1.59875;-0.01621;,
 -0.00941;-1.59875;-0.01621;;
 
 63;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;1,8,9,2;,
 4;2,9,10,4;,
 4;4,10,11,6;,
 4;8,12,13,9;,
 4;9,13,14,10;,
 4;10,14,15,11;,
 4;16,17,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;17,24,25,18;,
 4;18,25,26,20;,
 4;20,26,27,22;,
 4;24,28,29,25;,
 4;25,29,30,26;,
 4;26,30,31,27;,
 4;32,33,34,35;,
 4;35,34,36,37;,
 4;37,36,38,39;,
 4;33,40,41,34;,
 4;34,41,42,36;,
 4;36,42,43,38;,
 4;40,44,45,41;,
 4;41,45,46,42;,
 4;42,46,47,43;,
 4;48,49,50,51;,
 4;51,50,52,53;,
 4;53,52,54,55;,
 4;49,56,57,50;,
 4;50,57,58,52;,
 4;52,58,59,54;,
 4;56,60,61,57;,
 4;57,61,62,58;,
 4;58,62,63,59;,
 4;48,64,65,66;,
 4;66,65,67,68;,
 4;68,67,69,23;,
 4;64,70,71,65;,
 4;65,71,72,67;,
 4;67,72,73,69;,
 4;70,74,75,71;,
 4;71,75,76,72;,
 4;72,76,77,73;,
 4;78,60,79,80;,
 4;80,79,81,82;,
 4;82,81,31,83;,
 4;84,78,80,85;,
 4;85,80,82,86;,
 4;86,82,83,87;,
 4;88,84,85,89;,
 4;89,85,86,90;,
 4;90,86,87,91;,
 3;92,93,94;,
 3;95,94,96;,
 3;97,96,98;,
 3;99,100,93;,
 3;93,101,94;,
 3;94,102,96;,
 3;96,103,98;,
 3;92,99,93;,
 3;98,95,93;;
 
 MeshMaterialList {
  7;
  63;
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
  0,
  0,
  0;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.561600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.392000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.276000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.125600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  70;
  0.768879;0.207355;-0.604838;,
  0.359879;0.443091;-0.821071;,
  -0.238390;0.290099;-0.926830;,
  0.751224;-0.017536;-0.659814;,
  0.277858;-0.010207;-0.960568;,
  -0.109176;-0.006849;-0.993999;,
  0.799116;-0.037052;-0.600034;,
  0.334232;-0.027921;-0.942077;,
  -0.125919;-0.032302;-0.991515;,
  0.831746;-0.224686;-0.507657;,
  0.429831;-0.467289;-0.772584;,
  -0.136027;-0.052498;-0.989313;,
  -0.625642;0.298356;-0.720802;,
  -0.983672;-0.017898;-0.179079;,
  -0.978126;-0.031568;0.205606;,
  -0.651879;-0.021018;-0.758031;,
  -0.982662;-0.027625;-0.183338;,
  -0.969975;-0.044281;0.239138;,
  -0.670543;-0.048512;-0.740282;,
  -0.982845;-0.060114;-0.174364;,
  -0.960809;-0.074658;0.266968;,
  -0.672976;-0.362873;-0.644535;,
  -0.841080;-0.506710;-0.189287;,
  -0.809022;-0.471480;0.350985;,
  -0.623384;0.203272;0.755031;,
  -0.212132;0.363459;0.907137;,
  0.362218;0.318971;0.875817;,
  -0.663236;-0.091124;0.742842;,
  -0.187593;-0.110316;0.976032;,
  0.396062;-0.110167;0.911591;,
  -0.661129;-0.095360;0.744188;,
  -0.208820;-0.109746;0.971777;,
  0.480955;-0.101802;0.870815;,
  -0.593767;-0.276504;0.755636;,
  -0.212798;-0.378442;0.900832;,
  0.219017;-0.391055;0.893928;,
  0.712773;0.121777;0.690743;,
  0.859893;0.367080;0.354734;,
  0.896647;0.389758;-0.210031;,
  0.718623;-0.079722;0.690815;,
  0.922787;-0.035046;0.383713;,
  0.976263;-0.009884;-0.216363;,
  0.736560;-0.086264;0.670849;,
  0.885960;-0.108939;0.450786;,
  0.979934;-0.074127;-0.185024;,
  0.716224;-0.175962;0.675322;,
  0.791431;-0.401880;0.460575;,
  0.893524;-0.423769;-0.148443;,
  0.344302;0.869610;0.353885;,
  -0.209856;0.917015;0.339182;,
  0.370669;0.901181;-0.224673;,
  -0.210834;0.946854;-0.242933;,
  0.349986;-0.818055;0.456395;,
  -0.261259;-0.870669;0.416750;,
  0.375466;-0.906476;-0.193201;,
  -0.275883;-0.938739;-0.206538;,
  0.877388;-0.043601;0.477796;,
  -0.405322;0.850670;0.334775;,
  -0.413143;0.877239;-0.244467;,
  0.000000;0.893856;-0.448354;,
  -0.252783;-0.879947;-0.402237;,
  -0.577350;0.577349;0.577352;,
  0.577351;0.577351;-0.577350;,
  0.577349;0.577349;0.577352;,
  -0.577352;-0.577349;-0.577350;,
  -0.577351;-0.577348;0.577353;,
  0.577350;-0.577348;0.577353;,
  0.577351;-0.577349;-0.577350;,
  -0.577351;0.577350;-0.577349;,
  0.577351;-0.577350;0.577349;;
  63;
  4;0,3,4,1;,
  4;1,4,5,2;,
  4;2,5,15,12;,
  4;3,6,7,4;,
  4;4,7,8,5;,
  4;5,8,18,15;,
  4;6,9,10,7;,
  4;7,10,11,8;,
  4;8,11,21,18;,
  4;12,15,16,13;,
  4;13,16,17,14;,
  4;14,17,27,24;,
  4;15,18,19,16;,
  4;16,19,20,17;,
  4;17,20,30,27;,
  4;18,21,22,19;,
  4;19,22,23,20;,
  4;20,23,33,30;,
  4;24,27,28,25;,
  4;25,28,29,26;,
  4;26,29,39,36;,
  4;27,30,31,28;,
  4;28,31,32,29;,
  4;29,32,42,39;,
  4;30,33,34,31;,
  4;31,34,35,32;,
  4;32,56,45,42;,
  4;36,39,40,37;,
  4;37,40,41,38;,
  4;38,41,3,0;,
  4;39,42,43,40;,
  4;40,43,44,41;,
  4;41,44,6,3;,
  4;42,45,46,43;,
  4;43,46,47,44;,
  4;44,47,9,6;,
  4;36,37,48,26;,
  4;26,48,49,25;,
  4;25,49,57,24;,
  4;37,38,50,48;,
  4;48,50,51,49;,
  4;49,51,58,57;,
  4;38,0,1,50;,
  4;50,1,59,51;,
  4;51,2,12,58;,
  4;46,45,35,52;,
  4;52,35,34,53;,
  4;53,34,33,23;,
  4;47,46,52,54;,
  4;54,52,53,55;,
  4;55,53,23,22;,
  4;9,47,54,10;,
  4;10,54,55,60;,
  4;60,55,22,21;,
  3;61,61,61;,
  3;63,63,63;,
  3;62,62,62;,
  3;64,64,64;,
  3;65,65,65;,
  3;66,66,66;,
  3;67,67,67;,
  3;68,68,68;,
  3;69,69,69;;
 }
 MeshTextureCoords {
  104;
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.666670;,
  0.333330;1.000000;,
  0.333330;0.666670;,
  0.666670;1.000000;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.666670;0.333330;,
  1.000000;0.333330;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.666670;0.000000;,
  1.000000;0.000000;,
  0.375000;0.000000;,
  0.250000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.000000;,
  0.750000;0.500000;,
  0.875000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.875000;1.000000;;
 }
}