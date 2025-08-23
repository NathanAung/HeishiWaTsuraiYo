Create a copy of Release configuration called LocalRelease in the .vcxproj and change

<IncludePath>$(SIV3D_0_6_16)\include;$(SIV3D_0_6_16)\include\ThirdParty;$(IncludePath)</IncludePath>
<LibraryPath>$(SIV3D_0_6_16)\lib\Windows;$(LibraryPath)</LibraryPath>

to 

<IncludePath>$(SolutionDir)OpenSiv3D_SDK_0.6.16\include;$(SolutionDir)OpenSiv3D_SDK_0.6.16\include\ThirdParty;$(IncludePath)</IncludePath>
    <LibraryPath>$(SolutionDir)OpenSiv3D_SDK_0.6.16\lib\Windows;$(LibraryPath)</LibraryPath>

( basically change the souce form $(SIV3D_0_6_16) to $(SolutionDir)OpenSiv3D_SDK_0.6.16 )