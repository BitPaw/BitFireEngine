#######################################
# MakeFile Generator - BitFire Engine #
#######################################
#---Variables---#
Compiler = g++
DirExport = "__Export__"
DirTemp = "__Temp__"

all: folders $(DirExport)/ExportLib

folders: 
	-mkdir $(DirExport)
	-mkdir $(DirTemp)
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Resource.o: ./Resource.cpp
	@echo "[#] Compiling file ./Resource.cpp"
	-$(Compiler) -c "./Resource.cpp" -o $(DirTemp)/Resource.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Math.o: ./Math/Math.cpp
	@echo "[#] Compiling file ./Math/Math.cpp"
	-$(Compiler) -c "./Math/Math.cpp" -o $(DirTemp)/Math.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Interpolate.o: ./Math/Interpolate.cpp
	@echo "[#] Compiling file ./Math/Interpolate.cpp"
	-$(Compiler) -c "./Math/Interpolate.cpp" -o $(DirTemp)/Interpolate.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/BoxPlot.o: ./Math/Diagrams/BoxPlot.hpp
	@echo "[#] Compiling file ./Math/Diagrams/BoxPlot.hpp"
	-$(Compiler) -c "./Math/Diagrams/BoxPlot.hpp" -o $(DirTemp)/BoxPlot.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Vector4.o: ./Math/Geometry/Vector4.hpp
	@echo "[#] Compiling file ./Math/Geometry/Vector4.hpp"
	-$(Compiler) -c "./Math/Geometry/Vector4.hpp" -o $(DirTemp)/Vector4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/AngleRadians.o: ./Math/Geometry/AngleRadians.hpp
	@echo "[#] Compiling file ./Math/Geometry/AngleRadians.hpp"
	-$(Compiler) -c "./Math/Geometry/AngleRadians.hpp" -o $(DirTemp)/AngleRadians.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Vector3.o: ./Math/Geometry/Vector3.hpp
	@echo "[#] Compiling file ./Math/Geometry/Vector3.hpp"
	-$(Compiler) -c "./Math/Geometry/Vector3.hpp" -o $(DirTemp)/Vector3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Matrix3x3.o: ./Math/Geometry/Matrix3x3.hpp
	@echo "[#] Compiling file ./Math/Geometry/Matrix3x3.hpp"
	-$(Compiler) -c "./Math/Geometry/Matrix3x3.hpp" -o $(DirTemp)/Matrix3x3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Cylinder.o: ./Math/Geometry/Form/Cylinder.cpp
	@echo "[#] Compiling file ./Math/Geometry/Form/Cylinder.cpp"
	-$(Compiler) -c "./Math/Geometry/Form/Cylinder.cpp" -o $(DirTemp)/Cylinder.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/SquarePyramid.o: ./Math/Geometry/Form/SquarePyramid.cpp
	@echo "[#] Compiling file ./Math/Geometry/Form/SquarePyramid.cpp"
	-$(Compiler) -c "./Math/Geometry/Form/SquarePyramid.cpp" -o $(DirTemp)/SquarePyramid.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Cuboid.o: ./Math/Geometry/Form/Cuboid.cpp
	@echo "[#] Compiling file ./Math/Geometry/Form/Cuboid.cpp"
	-$(Compiler) -c "./Math/Geometry/Form/Cuboid.cpp" -o $(DirTemp)/Cuboid.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Sphere.o: ./Math/Geometry/Form/Sphere.cpp
	@echo "[#] Compiling file ./Math/Geometry/Form/Sphere.cpp"
	-$(Compiler) -c "./Math/Geometry/Form/Sphere.cpp" -o $(DirTemp)/Sphere.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Icosahedron.o: ./Math/Geometry/Form/Icosahedron.cpp
	@echo "[#] Compiling file ./Math/Geometry/Form/Icosahedron.cpp"
	-$(Compiler) -c "./Math/Geometry/Form/Icosahedron.cpp" -o $(DirTemp)/Icosahedron.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Cone.o: ./Math/Geometry/Form/Cone.cpp
	@echo "[#] Compiling file ./Math/Geometry/Form/Cone.cpp"
	-$(Compiler) -c "./Math/Geometry/Form/Cone.cpp" -o $(DirTemp)/Cone.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Form.o: ./Math/Geometry/Form/Form.cpp
	@echo "[#] Compiling file ./Math/Geometry/Form/Form.cpp"
	-$(Compiler) -c "./Math/Geometry/Form/Form.cpp" -o $(DirTemp)/Form.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Cube.o: ./Math/Geometry/Form/Cube.cpp
	@echo "[#] Compiling file ./Math/Geometry/Form/Cube.cpp"
	-$(Compiler) -c "./Math/Geometry/Form/Cube.cpp" -o $(DirTemp)/Cube.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Matrix4x4.o: ./Math/Geometry/Matrix4x4.hpp
	@echo "[#] Compiling file ./Math/Geometry/Matrix4x4.hpp"
	-$(Compiler) -c "./Math/Geometry/Matrix4x4.hpp" -o $(DirTemp)/Matrix4x4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Rectangle.o: ./Math/Geometry/Shape/Rectangle.cpp
	@echo "[#] Compiling file ./Math/Geometry/Shape/Rectangle.cpp"
	-$(Compiler) -c "./Math/Geometry/Shape/Rectangle.cpp" -o $(DirTemp)/Rectangle.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Triangle.o: ./Math/Geometry/Shape/Triangle.cpp
	@echo "[#] Compiling file ./Math/Geometry/Shape/Triangle.cpp"
	-$(Compiler) -c "./Math/Geometry/Shape/Triangle.cpp" -o $(DirTemp)/Triangle.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Pentagon.o: ./Math/Geometry/Shape/Pentagon.cpp
	@echo "[#] Compiling file ./Math/Geometry/Shape/Pentagon.cpp"
	-$(Compiler) -c "./Math/Geometry/Shape/Pentagon.cpp" -o $(DirTemp)/Pentagon.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Circle.o: ./Math/Geometry/Shape/Circle.cpp
	@echo "[#] Compiling file ./Math/Geometry/Shape/Circle.cpp"
	-$(Compiler) -c "./Math/Geometry/Shape/Circle.cpp" -o $(DirTemp)/Circle.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Shape.o: ./Math/Geometry/Shape/Shape.cpp
	@echo "[#] Compiling file ./Math/Geometry/Shape/Shape.cpp"
	-$(Compiler) -c "./Math/Geometry/Shape/Shape.cpp" -o $(DirTemp)/Shape.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Square.o: ./Math/Geometry/Shape/Square.cpp
	@echo "[#] Compiling file ./Math/Geometry/Shape/Square.cpp"
	-$(Compiler) -c "./Math/Geometry/Shape/Square.cpp" -o $(DirTemp)/Square.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Star.o: ./Math/Geometry/Shape/Star.cpp
	@echo "[#] Compiling file ./Math/Geometry/Shape/Star.cpp"
	-$(Compiler) -c "./Math/Geometry/Shape/Star.cpp" -o $(DirTemp)/Star.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Hexagon.o: ./Math/Geometry/Shape/Hexagon.cpp
	@echo "[#] Compiling file ./Math/Geometry/Shape/Hexagon.cpp"
	-$(Compiler) -c "./Math/Geometry/Shape/Hexagon.cpp" -o $(DirTemp)/Hexagon.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Matrix.o: ./Math/Geometry/Matrix.hpp
	@echo "[#] Compiling file ./Math/Geometry/Matrix.hpp"
	-$(Compiler) -c "./Math/Geometry/Matrix.hpp" -o $(DirTemp)/Matrix.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Padding.o: ./Math/Geometry/Padding.hpp
	@echo "[#] Compiling file ./Math/Geometry/Padding.hpp"
	-$(Compiler) -c "./Math/Geometry/Padding.hpp" -o $(DirTemp)/Padding.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Vector2.o: ./Math/Geometry/Vector2.hpp
	@echo "[#] Compiling file ./Math/Geometry/Vector2.hpp"
	-$(Compiler) -c "./Math/Geometry/Vector2.hpp" -o $(DirTemp)/Vector2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Matrix2x2.o: ./Math/Geometry/Matrix2x2.hpp
	@echo "[#] Compiling file ./Math/Geometry/Matrix2x2.hpp"
	-$(Compiler) -c "./Math/Geometry/Matrix2x2.hpp" -o $(DirTemp)/Matrix2x2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/AngleDegree.o: ./Math/Geometry/AngleDegree.hpp
	@echo "[#] Compiling file ./Math/Geometry/AngleDegree.hpp"
	-$(Compiler) -c "./Math/Geometry/AngleDegree.hpp" -o $(DirTemp)/AngleDegree.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PhysicsStatic.o: ./Math/Physic/PhysicsStatic.hpp
	@echo "[#] Compiling file ./Math/Physic/PhysicsStatic.hpp"
	-$(Compiler) -c "./Math/Physic/PhysicsStatic.hpp" -o $(DirTemp)/PhysicsStatic.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/GravitySphere.o: ./Math/Physic/GravitySphere.cpp
	@echo "[#] Compiling file ./Math/Physic/GravitySphere.cpp"
	-$(Compiler) -c "./Math/Physic/GravitySphere.cpp" -o $(DirTemp)/GravitySphere.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PhysicsDynamic.o: ./Math/Physic/PhysicsDynamic.hpp
	@echo "[#] Compiling file ./Math/Physic/PhysicsDynamic.hpp"
	-$(Compiler) -c "./Math/Physic/PhysicsDynamic.hpp" -o $(DirTemp)/PhysicsDynamic.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Collider.o: ./Math/Physic/Collider.cpp
	@echo "[#] Compiling file ./Math/Physic/Collider.cpp"
	-$(Compiler) -c "./Math/Physic/Collider.cpp" -o $(DirTemp)/Collider.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/GravityField.o: ./Math/Physic/GravityField.cpp
	@echo "[#] Compiling file ./Math/Physic/GravityField.cpp"
	-$(Compiler) -c "./Math/Physic/GravityField.cpp" -o $(DirTemp)/GravityField.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/GravityCube.o: ./Math/Physic/GravityCube.cpp
	@echo "[#] Compiling file ./Math/Physic/GravityCube.cpp"
	-$(Compiler) -c "./Math/Physic/GravityCube.cpp" -o $(DirTemp)/GravityCube.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MP3ChannelMode.o: ./Sound/MP3/MP3ChannelMode.hpp
	@echo "[#] Compiling file ./Sound/MP3/MP3ChannelMode.hpp"
	-$(Compiler) -c "./Sound/MP3/MP3ChannelMode.hpp" -o $(DirTemp)/MP3ChannelMode.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MP3MPEGVersion.o: ./Sound/MP3/MP3MPEGVersion.hpp
	@echo "[#] Compiling file ./Sound/MP3/MP3MPEGVersion.hpp"
	-$(Compiler) -c "./Sound/MP3/MP3MPEGVersion.hpp" -o $(DirTemp)/MP3MPEGVersion.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MPEGGenre.o: ./Sound/MP3/MPEGGenre.cpp
	@echo "[#] Compiling file ./Sound/MP3/MPEGGenre.cpp"
	-$(Compiler) -c "./Sound/MP3/MPEGGenre.cpp" -o $(DirTemp)/MPEGGenre.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MP3Layer.o: ./Sound/MP3/MP3Layer.hpp
	@echo "[#] Compiling file ./Sound/MP3/MP3Layer.hpp"
	-$(Compiler) -c "./Sound/MP3/MP3Layer.hpp" -o $(DirTemp)/MP3Layer.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MP3.o: ./Sound/MP3/MP3.cpp
	@echo "[#] Compiling file ./Sound/MP3/MP3.cpp"
	-$(Compiler) -c "./Sound/MP3/MP3.cpp" -o $(DirTemp)/MP3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MP3Emphasis.o: ./Sound/MP3/MP3Emphasis.hpp
	@echo "[#] Compiling file ./Sound/MP3/MP3Emphasis.hpp"
	-$(Compiler) -c "./Sound/MP3/MP3Emphasis.hpp" -o $(DirTemp)/MP3Emphasis.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MP3Header.o: ./Sound/MP3/MP3Header.cpp
	@echo "[#] Compiling file ./Sound/MP3/MP3Header.cpp"
	-$(Compiler) -c "./Sound/MP3/MP3Header.cpp" -o $(DirTemp)/MP3Header.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MPEGGenre.o: ./Sound/MP3/MPEGGenre.hpp
	@echo "[#] Compiling file ./Sound/MP3/MPEGGenre.hpp"
	-$(Compiler) -c "./Sound/MP3/MPEGGenre.hpp" -o $(DirTemp)/MPEGGenre.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MPEGAudioTag.o: ./Sound/MP3/MPEGAudioTag.cpp
	@echo "[#] Compiling file ./Sound/MP3/MPEGAudioTag.cpp"
	-$(Compiler) -c "./Sound/MP3/MPEGAudioTag.cpp" -o $(DirTemp)/MPEGAudioTag.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/SoundPlayStyle.o: ./Sound/SoundPlayStyle.hpp
	@echo "[#] Compiling file ./Sound/SoundPlayStyle.hpp"
	-$(Compiler) -c "./Sound/SoundPlayStyle.hpp" -o $(DirTemp)/SoundPlayStyle.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FMT.o: ./Sound/WAV/FMT.cpp
	@echo "[#] Compiling file ./Sound/WAV/FMT.cpp"
	-$(Compiler) -c "./Sound/WAV/FMT.cpp" -o $(DirTemp)/FMT.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/RIFF.o: ./Sound/WAV/RIFF.cpp
	@echo "[#] Compiling file ./Sound/WAV/RIFF.cpp"
	-$(Compiler) -c "./Sound/WAV/RIFF.cpp" -o $(DirTemp)/RIFF.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/WAV.o: ./Sound/WAV/WAV.cpp
	@echo "[#] Compiling file ./Sound/WAV/WAV.cpp"
	-$(Compiler) -c "./Sound/WAV/WAV.cpp" -o $(DirTemp)/WAV.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/M4A.o: ./Sound/M4A/M4A.cpp
	@echo "[#] Compiling file ./Sound/M4A/M4A.cpp"
	-$(Compiler) -c "./Sound/M4A/M4A.cpp" -o $(DirTemp)/M4A.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Sound.o: ./Sound/Sound.cpp
	@echo "[#] Compiling file ./Sound/Sound.cpp"
	-$(Compiler) -c "./Sound/Sound.cpp" -o $(DirTemp)/Sound.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/WMA.o: ./Sound/WMA/WMA.cpp
	@echo "[#] Compiling file ./Sound/WMA/WMA.cpp"
	-$(Compiler) -c "./Sound/WMA/WMA.cpp" -o $(DirTemp)/WMA.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/OGG.o: ./Sound/OGG/OGG.cpp
	@echo "[#] Compiling file ./Sound/OGG/OGG.cpp"
	-$(Compiler) -c "./Sound/OGG/OGG.cpp" -o $(DirTemp)/OGG.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FLAC.o: ./Sound/FLAC/FLAC.cpp
	@echo "[#] Compiling file ./Sound/FLAC/FLAC.cpp"
	-$(Compiler) -c "./Sound/FLAC/FLAC.cpp" -o $(DirTemp)/FLAC.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MIDITrackHeader.o: ./Sound/MID/MIDITrackHeader.cpp
	@echo "[#] Compiling file ./Sound/MID/MIDITrackHeader.cpp"
	-$(Compiler) -c "./Sound/MID/MIDITrackHeader.cpp" -o $(DirTemp)/MIDITrackHeader.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MIDICommandExtended.o: ./Sound/MID/MIDICommandExtended.cpp
	@echo "[#] Compiling file ./Sound/MID/MIDICommandExtended.cpp"
	-$(Compiler) -c "./Sound/MID/MIDICommandExtended.cpp" -o $(DirTemp)/MIDICommandExtended.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MID.o: ./Sound/MID/MID.cpp
	@echo "[#] Compiling file ./Sound/MID/MID.cpp"
	-$(Compiler) -c "./Sound/MID/MID.cpp" -o $(DirTemp)/MID.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MIDINote.o: ./Sound/MID/MIDINote.cpp
	@echo "[#] Compiling file ./Sound/MID/MIDINote.cpp"
	-$(Compiler) -c "./Sound/MID/MIDINote.cpp" -o $(DirTemp)/MIDINote.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MIDICommand.o: ./Sound/MID/MIDICommand.cpp
	@echo "[#] Compiling file ./Sound/MID/MIDICommand.cpp"
	-$(Compiler) -c "./Sound/MID/MIDICommand.cpp" -o $(DirTemp)/MIDICommand.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MIDITrack.o: ./Sound/MID/MIDITrack.cpp
	@echo "[#] Compiling file ./Sound/MID/MIDITrack.cpp"
	-$(Compiler) -c "./Sound/MID/MIDITrack.cpp" -o $(DirTemp)/MIDITrack.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/AAC.o: ./Sound/AAC/AAC.cpp
	@echo "[#] Compiling file ./Sound/AAC/AAC.cpp"
	-$(Compiler) -c "./Sound/AAC/AAC.cpp" -o $(DirTemp)/AAC.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ISoundFormat.o: ./Sound/ISoundFormat.hpp
	@echo "[#] Compiling file ./Sound/ISoundFormat.hpp"
	-$(Compiler) -c "./Sound/ISoundFormat.hpp" -o $(DirTemp)/ISoundFormat.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ICypher.o: ./Encryption/ICypher.cpp
	@echo "[#] Compiling file ./Encryption/ICypher.cpp"
	-$(Compiler) -c "./Encryption/ICypher.cpp" -o $(DirTemp)/ICypher.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/RSA.o: ./Encryption/RSA.cpp
	@echo "[#] Compiling file ./Encryption/RSA.cpp"
	-$(Compiler) -c "./Encryption/RSA.cpp" -o $(DirTemp)/RSA.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Caesar.o: ./Encryption/Caesar.cpp
	@echo "[#] Compiling file ./Encryption/Caesar.cpp"
	-$(Compiler) -c "./Encryption/Caesar.cpp" -o $(DirTemp)/Caesar.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ResourceType.o: ./ResourceType.hpp
	@echo "[#] Compiling file ./ResourceType.hpp"
	-$(Compiler) -c "./ResourceType.hpp" -o $(DirTemp)/ResourceType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Video.o: ./Video/Video.cpp
	@echo "[#] Compiling file ./Video/Video.cpp"
	-$(Compiler) -c "./Video/Video.cpp" -o $(DirTemp)/Video.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MP4.o: ./Video/MP4/MP4.cpp
	@echo "[#] Compiling file ./Video/MP4/MP4.cpp"
	-$(Compiler) -c "./Video/MP4/MP4.cpp" -o $(DirTemp)/MP4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IVideoFormat.o: ./Video/IVideoFormat.hpp
	@echo "[#] Compiling file ./Video/IVideoFormat.hpp"
	-$(Compiler) -c "./Video/IVideoFormat.hpp" -o $(DirTemp)/IVideoFormat.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/AVI.o: ./Video/AVI/AVI.cpp
	@echo "[#] Compiling file ./Video/AVI/AVI.cpp"
	-$(Compiler) -c "./Video/AVI/AVI.cpp" -o $(DirTemp)/AVI.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/AVIHeader.o: ./Video/AVI/AVIHeader.cpp
	@echo "[#] Compiling file ./Video/AVI/AVIHeader.cpp"
	-$(Compiler) -c "./Video/AVI/AVIHeader.cpp" -o $(DirTemp)/AVIHeader.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Dialog.o: ./Dialog/Dialog.cpp
	@echo "[#] Compiling file ./Dialog/Dialog.cpp"
	-$(Compiler) -c "./Dialog/Dialog.cpp" -o $(DirTemp)/Dialog.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FNTCharacter.o: ./Font/FNT/FNTCharacter.cpp
	@echo "[#] Compiling file ./Font/FNT/FNTCharacter.cpp"
	-$(Compiler) -c "./Font/FNT/FNTCharacter.cpp" -o $(DirTemp)/FNTCharacter.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FNTInfo.o: ./Font/FNT/FNTInfo.cpp
	@echo "[#] Compiling file ./Font/FNT/FNTInfo.cpp"
	-$(Compiler) -c "./Font/FNT/FNTInfo.cpp" -o $(DirTemp)/FNTInfo.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FNTPage.o: ./Font/FNT/FNTPage.cpp
	@echo "[#] Compiling file ./Font/FNT/FNTPage.cpp"
	-$(Compiler) -c "./Font/FNT/FNTPage.cpp" -o $(DirTemp)/FNTPage.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FNT.o: ./Font/FNT/FNT.cpp
	@echo "[#] Compiling file ./Font/FNT/FNT.cpp"
	-$(Compiler) -c "./Font/FNT/FNT.cpp" -o $(DirTemp)/FNT.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FNTCommonData.o: ./Font/FNT/FNTCommonData.cpp
	@echo "[#] Compiling file ./Font/FNT/FNTCommonData.cpp"
	-$(Compiler) -c "./Font/FNT/FNTCommonData.cpp" -o $(DirTemp)/FNTCommonData.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IFontFormat.o: ./Font/IFontFormat.hpp
	@echo "[#] Compiling file ./Font/IFontFormat.hpp"
	-$(Compiler) -c "./Font/IFontFormat.hpp" -o $(DirTemp)/IFontFormat.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/OTF.o: ./Font/OTF/OTF.cpp
	@echo "[#] Compiling file ./Font/OTF/OTF.cpp"
	-$(Compiler) -c "./Font/OTF/OTF.cpp" -o $(DirTemp)/OTF.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Font.o: ./Font/Font.cpp
	@echo "[#] Compiling file ./Font/Font.cpp"
	-$(Compiler) -c "./Font/Font.cpp" -o $(DirTemp)/Font.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTF.o: ./Font/TTF/TTF.cpp
	@echo "[#] Compiling file ./Font/TTF/TTF.cpp"
	-$(Compiler) -c "./Font/TTF/TTF.cpp" -o $(DirTemp)/TTF.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFTableEntry.o: ./Font/TTF/TTFTableEntry.cpp
	@echo "[#] Compiling file ./Font/TTF/TTFTableEntry.cpp"
	-$(Compiler) -c "./Font/TTF/TTFTableEntry.cpp" -o $(DirTemp)/TTFTableEntry.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFVersion.o: ./Font/TTF/Chunks/TTFVersion.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/TTFVersion.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/TTFVersion.cpp" -o $(DirTemp)/TTFVersion.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFHeader.o: ./Font/TTF/Chunks/TTFHeader.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/TTFHeader.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/TTFHeader.cpp" -o $(DirTemp)/TTFHeader.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/EncodingID.o: ./Font/TTF/Chunks/CMAP/EncodingID.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/CMAP/EncodingID.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/CMAP/EncodingID.cpp" -o $(DirTemp)/EncodingID.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PlatformID.o: ./Font/TTF/Chunks/CMAP/PlatformID.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/CMAP/PlatformID.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/CMAP/PlatformID.cpp" -o $(DirTemp)/PlatformID.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFCharacterMapping.o: ./Font/TTF/Chunks/CMAP/TTFCharacterMapping.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/CMAP/TTFCharacterMapping.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/CMAP/TTFCharacterMapping.cpp" -o $(DirTemp)/TTFCharacterMapping.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/EncodingRecord.o: ./Font/TTF/Chunks/CMAP/EncodingRecord.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/CMAP/EncodingRecord.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/CMAP/EncodingRecord.cpp" -o $(DirTemp)/EncodingRecord.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFOffsetTable.o: ./Font/TTF/Chunks/TTFOffsetTable.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/TTFOffsetTable.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/TTFOffsetTable.cpp" -o $(DirTemp)/TTFOffsetTable.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFVersionType.o: ./Font/TTF/Chunks/TTFVersionType.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/TTFVersionType.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/TTFVersionType.cpp" -o $(DirTemp)/TTFVersionType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFCompatibility.o: ./Font/TTF/Chunks/OS2/TTFCompatibility.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/OS2/TTFCompatibility.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/OS2/TTFCompatibility.cpp" -o $(DirTemp)/TTFCompatibility.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFLetterform.o: ./Font/TTF/Chunks/OS2/Panose/TTFLetterform.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/OS2/Panose/TTFLetterform.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/OS2/Panose/TTFLetterform.cpp" -o $(DirTemp)/TTFLetterform.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFContrast.o: ./Font/TTF/Chunks/OS2/Panose/TTFContrast.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/OS2/Panose/TTFContrast.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/OS2/Panose/TTFContrast.cpp" -o $(DirTemp)/TTFContrast.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFMidline.o: ./Font/TTF/Chunks/OS2/Panose/TTFMidline.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/OS2/Panose/TTFMidline.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/OS2/Panose/TTFMidline.cpp" -o $(DirTemp)/TTFMidline.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFPanose.o: ./Font/TTF/Chunks/OS2/Panose/TTFPanose.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/OS2/Panose/TTFPanose.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/OS2/Panose/TTFPanose.cpp" -o $(DirTemp)/TTFPanose.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFArmStyle.o: ./Font/TTF/Chunks/OS2/Panose/TTFArmStyle.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/OS2/Panose/TTFArmStyle.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/OS2/Panose/TTFArmStyle.cpp" -o $(DirTemp)/TTFArmStyle.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFProportion.o: ./Font/TTF/Chunks/OS2/Panose/TTFProportion.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/OS2/Panose/TTFProportion.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/OS2/Panose/TTFProportion.cpp" -o $(DirTemp)/TTFProportion.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFWeight.o: ./Font/TTF/Chunks/OS2/Panose/TTFWeight.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/OS2/Panose/TTFWeight.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/OS2/Panose/TTFWeight.cpp" -o $(DirTemp)/TTFWeight.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFHeightX.o: ./Font/TTF/Chunks/OS2/Panose/TTFHeightX.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/OS2/Panose/TTFHeightX.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/OS2/Panose/TTFHeightX.cpp" -o $(DirTemp)/TTFHeightX.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFSerifStyle.o: ./Font/TTF/Chunks/OS2/Panose/TTFSerifStyle.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/OS2/Panose/TTFSerifStyle.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/OS2/Panose/TTFSerifStyle.cpp" -o $(DirTemp)/TTFSerifStyle.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFStrokeVariatoon.o: ./Font/TTF/Chunks/OS2/Panose/TTFStrokeVariatoon.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/OS2/Panose/TTFStrokeVariatoon.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/OS2/Panose/TTFStrokeVariatoon.cpp" -o $(DirTemp)/TTFStrokeVariatoon.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFFamilyType.o: ./Font/TTF/Chunks/OS2/Panose/TTFFamilyType.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/OS2/Panose/TTFFamilyType.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/OS2/Panose/TTFFamilyType.cpp" -o $(DirTemp)/TTFFamilyType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFHorizontalHeader.o: ./Font/TTF/Chunks/TTFHorizontalHeader.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/TTFHorizontalHeader.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/TTFHorizontalHeader.cpp" -o $(DirTemp)/TTFHorizontalHeader.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFKerning.o: ./Font/TTF/Chunks/KERN/TTFKerning.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/KERN/TTFKerning.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/KERN/TTFKerning.cpp" -o $(DirTemp)/TTFKerning.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFSubtableFormat0.o: ./Font/TTF/Chunks/KERN/TTFSubtableFormat0.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/KERN/TTFSubtableFormat0.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/KERN/TTFSubtableFormat0.cpp" -o $(DirTemp)/TTFSubtableFormat0.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFKerningSubtable.o: ./Font/TTF/Chunks/KERN/TTFKerningSubtable.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/KERN/TTFKerningSubtable.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/KERN/TTFKerningSubtable.cpp" -o $(DirTemp)/TTFKerningSubtable.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFSubtableFormat2.o: ./Font/TTF/Chunks/KERN/TTFSubtableFormat2.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/KERN/TTFSubtableFormat2.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/KERN/TTFSubtableFormat2.cpp" -o $(DirTemp)/TTFSubtableFormat2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFKerningPair.o: ./Font/TTF/Chunks/KERN/TTFKerningPair.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/KERN/TTFKerningPair.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/KERN/TTFKerningPair.cpp" -o $(DirTemp)/TTFKerningPair.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFPostScript.o: ./Font/TTF/Chunks/TTFPostScript.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/TTFPostScript.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/TTFPostScript.cpp" -o $(DirTemp)/TTFPostScript.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFMaximumProfile.o: ./Font/TTF/Chunks/TTFMaximumProfile.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/TTFMaximumProfile.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/TTFMaximumProfile.cpp" -o $(DirTemp)/TTFMaximumProfile.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFLinearThreshold.o: ./Font/TTF/Chunks/TTFLinearThreshold.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/TTFLinearThreshold.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/TTFLinearThreshold.cpp" -o $(DirTemp)/TTFLinearThreshold.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFDigitalSignatureBlock.o: ./Font/TTF/Chunks/DSIG/TTFDigitalSignatureBlock.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/DSIG/TTFDigitalSignatureBlock.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/DSIG/TTFDigitalSignatureBlock.cpp" -o $(DirTemp)/TTFDigitalSignatureBlock.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFDigitalSignatureRecord.o: ./Font/TTF/Chunks/DSIG/TTFDigitalSignatureRecord.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/DSIG/TTFDigitalSignatureRecord.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/DSIG/TTFDigitalSignatureRecord.cpp" -o $(DirTemp)/TTFDigitalSignatureRecord.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFDigitalSignature.o: ./Font/TTF/Chunks/DSIG/TTFDigitalSignature.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/DSIG/TTFDigitalSignature.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/DSIG/TTFDigitalSignature.cpp" -o $(DirTemp)/TTFDigitalSignature.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFVerticalDeviceMetrics.o: ./Font/TTF/Chunks/TTFVerticalDeviceMetrics.cpp
	@echo "[#] Compiling file ./Font/TTF/Chunks/TTFVerticalDeviceMetrics.cpp"
	-$(Compiler) -c "./Font/TTF/Chunks/TTFVerticalDeviceMetrics.cpp" -o $(DirTemp)/TTFVerticalDeviceMetrics.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFTableEntryType.o: ./Font/TTF/TTFTableEntryType.cpp
	@echo "[#] Compiling file ./Font/TTF/TTFTableEntryType.cpp"
	-$(Compiler) -c "./Font/TTF/TTFTableEntryType.cpp" -o $(DirTemp)/TTFTableEntryType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Event.o: ./Event/Event.hpp
	@echo "[#] Compiling file ./Event/Event.hpp"
	-$(Compiler) -c "./Event/Event.hpp" -o $(DirTemp)/Event.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FBX.o: ./Model/FBX/FBX.cpp
	@echo "[#] Compiling file ./Model/FBX/FBX.cpp"
	-$(Compiler) -c "./Model/FBX/FBX.cpp" -o $(DirTemp)/FBX.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Material.o: ./Model/Material.cpp
	@echo "[#] Compiling file ./Model/Material.cpp"
	-$(Compiler) -c "./Model/Material.cpp" -o $(DirTemp)/Material.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Model.o: ./Model/Model.cpp
	@echo "[#] Compiling file ./Model/Model.cpp"
	-$(Compiler) -c "./Model/Model.cpp" -o $(DirTemp)/Model.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MeshStructure.o: ./Model/MeshStructure.cpp
	@echo "[#] Compiling file ./Model/MeshStructure.cpp"
	-$(Compiler) -c "./Model/MeshStructure.cpp" -o $(DirTemp)/MeshStructure.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/A3DS.o: ./Model/3DS/A3DS.cpp
	@echo "[#] Compiling file ./Model/3DS/A3DS.cpp"
	-$(Compiler) -c "./Model/3DS/A3DS.cpp" -o $(DirTemp)/A3DS.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Mesh.o: ./Model/Mesh.cpp
	@echo "[#] Compiling file ./Model/Mesh.cpp"
	-$(Compiler) -c "./Model/Mesh.cpp" -o $(DirTemp)/Mesh.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IModelFormat.o: ./Model/IModelFormat.hpp
	@echo "[#] Compiling file ./Model/IModelFormat.hpp"
	-$(Compiler) -c "./Model/IModelFormat.hpp" -o $(DirTemp)/IModelFormat.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MeshRenderInfo.o: ./Model/MeshRenderInfo.cpp
	@echo "[#] Compiling file ./Model/MeshRenderInfo.cpp"
	-$(Compiler) -c "./Model/MeshRenderInfo.cpp" -o $(DirTemp)/MeshRenderInfo.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Vertex.o: ./Model/Vertex.cpp
	@echo "[#] Compiling file ./Model/Vertex.cpp"
	-$(Compiler) -c "./Model/Vertex.cpp" -o $(DirTemp)/Vertex.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/WRL.o: ./Model/WRL/WRL.cpp
	@echo "[#] Compiling file ./Model/WRL/WRL.cpp"
	-$(Compiler) -c "./Model/WRL/WRL.cpp" -o $(DirTemp)/WRL.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/LinkedMesh.o: ./Model/LinkedMesh.cpp
	@echo "[#] Compiling file ./Model/LinkedMesh.cpp"
	-$(Compiler) -c "./Model/LinkedMesh.cpp" -o $(DirTemp)/LinkedMesh.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/STL.o: ./Model/STL/STL.cpp
	@echo "[#] Compiling file ./Model/STL/STL.cpp"
	-$(Compiler) -c "./Model/STL/STL.cpp" -o $(DirTemp)/STL.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PLY.o: ./Model/PLY/PLY.cpp
	@echo "[#] Compiling file ./Model/PLY/PLY.cpp"
	-$(Compiler) -c "./Model/PLY/PLY.cpp" -o $(DirTemp)/PLY.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/OBJ.o: ./Model/OBJ/OBJ.cpp
	@echo "[#] Compiling file ./Model/OBJ/OBJ.cpp"
	-$(Compiler) -c "./Model/OBJ/OBJ.cpp" -o $(DirTemp)/OBJ.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MTL.o: ./Model/OBJ/MTL/MTL.cpp
	@echo "[#] Compiling file ./Model/OBJ/MTL/MTL.cpp"
	-$(Compiler) -c "./Model/OBJ/MTL/MTL.cpp" -o $(DirTemp)/MTL.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/OBJElement.o: ./Model/OBJ/OBJElement.cpp
	@echo "[#] Compiling file ./Model/OBJ/OBJElement.cpp"
	-$(Compiler) -c "./Model/OBJ/OBJElement.cpp" -o $(DirTemp)/OBJElement.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MeshIndexData.o: ./Model/MeshIndexData.cpp
	@echo "[#] Compiling file ./Model/MeshIndexData.cpp"
	-$(Compiler) -c "./Model/MeshIndexData.cpp" -o $(DirTemp)/MeshIndexData.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/HTTPServer.o: ./Service/HTTP/HTTPServer.cpp
	@echo "[#] Compiling file ./Service/HTTP/HTTPServer.cpp"
	-$(Compiler) -c "./Service/HTTP/HTTPServer.cpp" -o $(DirTemp)/HTTPServer.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/HTTPError.o: ./Service/HTTP/HTTPError.cpp
	@echo "[#] Compiling file ./Service/HTTP/HTTPError.cpp"
	-$(Compiler) -c "./Service/HTTP/HTTPError.cpp" -o $(DirTemp)/HTTPError.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/HTTPRequestMethod.o: ./Service/HTTP/HTTPRequestMethod.cpp
	@echo "[#] Compiling file ./Service/HTTP/HTTPRequestMethod.cpp"
	-$(Compiler) -c "./Service/HTTP/HTTPRequestMethod.cpp" -o $(DirTemp)/HTTPRequestMethod.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ADAM7.o: ./Compression/ADAM7/ADAM7.cpp
	@echo "[#] Compiling file ./Compression/ADAM7/ADAM7.cpp"
	-$(Compiler) -c "./Compression/ADAM7/ADAM7.cpp" -o $(DirTemp)/ADAM7.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ZLIB.o: ./Compression/ZLIB/ZLIB.cpp
	@echo "[#] Compiling file ./Compression/ZLIB/ZLIB.cpp"
	-$(Compiler) -c "./Compression/ZLIB/ZLIB.cpp" -o $(DirTemp)/ZLIB.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ZLIBHeader.o: ./Compression/ZLIB/ZLIBHeader.cpp
	@echo "[#] Compiling file ./Compression/ZLIB/ZLIBHeader.cpp"
	-$(Compiler) -c "./Compression/ZLIB/ZLIBHeader.cpp" -o $(DirTemp)/ZLIBHeader.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ZLIBCompressionMethod.o: ./Compression/ZLIB/ZLIBCompressionMethod.cpp
	@echo "[#] Compiling file ./Compression/ZLIB/ZLIBCompressionMethod.cpp"
	-$(Compiler) -c "./Compression/ZLIB/ZLIBCompressionMethod.cpp" -o $(DirTemp)/ZLIBCompressionMethod.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ZLIBCompressionLevel.o: ./Compression/ZLIB/ZLIBCompressionLevel.cpp
	@echo "[#] Compiling file ./Compression/ZLIB/ZLIBCompressionLevel.cpp"
	-$(Compiler) -c "./Compression/ZLIB/ZLIBCompressionLevel.cpp" -o $(DirTemp)/ZLIBCompressionLevel.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/HuffmanCodeType.o: ./Compression/HUFFMAN/HuffmanCodeType.cpp
	@echo "[#] Compiling file ./Compression/HUFFMAN/HuffmanCodeType.cpp"
	-$(Compiler) -c "./Compression/HUFFMAN/HuffmanCodeType.cpp" -o $(DirTemp)/HuffmanCodeType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/HuffmanTree.o: ./Compression/HUFFMAN/HuffmanTree.cpp
	@echo "[#] Compiling file ./Compression/HUFFMAN/HuffmanTree.cpp"
	-$(Compiler) -c "./Compression/HUFFMAN/HuffmanTree.cpp" -o $(DirTemp)/HuffmanTree.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/HuffmanSymbol.o: ./Compression/HUFFMAN/HuffmanSymbol.cpp
	@echo "[#] Compiling file ./Compression/HUFFMAN/HuffmanSymbol.cpp"
	-$(Compiler) -c "./Compression/HUFFMAN/HuffmanSymbol.cpp" -o $(DirTemp)/HuffmanSymbol.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/HuffmanNumberCode.o: ./Compression/HUFFMAN/HuffmanNumberCode.cpp
	@echo "[#] Compiling file ./Compression/HUFFMAN/HuffmanNumberCode.cpp"
	-$(Compiler) -c "./Compression/HUFFMAN/HuffmanNumberCode.cpp" -o $(DirTemp)/HuffmanNumberCode.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/DeflateBlock.o: ./Compression/DEFLATE/DeflateBlock.cpp
	@echo "[#] Compiling file ./Compression/DEFLATE/DeflateBlock.cpp"
	-$(Compiler) -c "./Compression/DEFLATE/DeflateBlock.cpp" -o $(DirTemp)/DeflateBlock.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/DeflateEncodingMethod.o: ./Compression/DEFLATE/DeflateEncodingMethod.cpp
	@echo "[#] Compiling file ./Compression/DEFLATE/DeflateEncodingMethod.cpp"
	-$(Compiler) -c "./Compression/DEFLATE/DeflateEncodingMethod.cpp" -o $(DirTemp)/DeflateEncodingMethod.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Bash.o: ./File/Bash.cpp
	@echo "[#] Compiling file ./File/Bash.cpp"
	-$(Compiler) -c "./File/Bash.cpp" -o $(DirTemp)/Bash.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FileStream.o: ./File/FileStream.cpp
	@echo "[#] Compiling file ./File/FileStream.cpp"
	-$(Compiler) -c "./File/FileStream.cpp" -o $(DirTemp)/FileStream.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ProgramExecuteResultListener.o: ./File/ProgramExecuteResultListener.hpp
	@echo "[#] Compiling file ./File/ProgramExecuteResultListener.hpp"
	-$(Compiler) -c "./File/ProgramExecuteResultListener.hpp" -o $(DirTemp)/ProgramExecuteResultListener.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FileOpenMode.o: ./File/FileOpenMode.hpp
	@echo "[#] Compiling file ./File/FileOpenMode.hpp"
	-$(Compiler) -c "./File/FileOpenMode.hpp" -o $(DirTemp)/FileOpenMode.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ProgramExecuteInfo.o: ./File/ProgramExecuteInfo.cpp
	@echo "[#] Compiling file ./File/ProgramExecuteInfo.cpp"
	-$(Compiler) -c "./File/ProgramExecuteInfo.cpp" -o $(DirTemp)/ProgramExecuteInfo.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ByteStream.o: ./File/ByteStream.cpp
	@echo "[#] Compiling file ./File/ByteStream.cpp"
	-$(Compiler) -c "./File/ByteStream.cpp" -o $(DirTemp)/ByteStream.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FilePersistence.o: ./File/FilePersistence.hpp
	@echo "[#] Compiling file ./File/FilePersistence.hpp"
	-$(Compiler) -c "./File/FilePersistence.hpp" -o $(DirTemp)/FilePersistence.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IFIle.o: ./File/IFIle.cpp
	@echo "[#] Compiling file ./File/IFIle.cpp"
	-$(Compiler) -c "./File/IFIle.cpp" -o $(DirTemp)/IFIle.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FileTemporary.o: ./File/FileTemporary.cpp
	@echo "[#] Compiling file ./File/FileTemporary.cpp"
	-$(Compiler) -c "./File/FileTemporary.cpp" -o $(DirTemp)/FileTemporary.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FileActionResult.o: ./File/FileActionResult.hpp
	@echo "[#] Compiling file ./File/FileActionResult.hpp"
	-$(Compiler) -c "./File/FileActionResult.hpp" -o $(DirTemp)/FileActionResult.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/OpenFileDialog.o: ./File/OpenFileDialog.cpp
	@echo "[#] Compiling file ./File/OpenFileDialog.cpp"
	-$(Compiler) -c "./File/OpenFileDialog.cpp" -o $(DirTemp)/OpenFileDialog.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Program.o: ./File/Program.cpp
	@echo "[#] Compiling file ./File/Program.cpp"
	-$(Compiler) -c "./File/Program.cpp" -o $(DirTemp)/Program.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/File.o: ./File/File.cpp
	@echo "[#] Compiling file ./File/File.cpp"
	-$(Compiler) -c "./File/File.cpp" -o $(DirTemp)/File.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Level.o: ./Level/Level.cpp
	@echo "[#] Compiling file ./Level/Level.cpp"
	-$(Compiler) -c "./Level/Level.cpp" -o $(DirTemp)/Level.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/SkyBox.o: ./Game/SkyBox.cpp
	@echo "[#] Compiling file ./Game/SkyBox.cpp"
	-$(Compiler) -c "./Game/SkyBox.cpp" -o $(DirTemp)/SkyBox.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Sprite.o: ./Game/Sprite.cpp
	@echo "[#] Compiling file ./Game/Sprite.cpp"
	-$(Compiler) -c "./Game/Sprite.cpp" -o $(DirTemp)/Sprite.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/EML.o: ./Email/EML.cpp
	@echo "[#] Compiling file ./Email/EML.cpp"
	-$(Compiler) -c "./Email/EML.cpp" -o $(DirTemp)/EML.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ShaderType.o: ./Shader/ShaderType.cpp
	@echo "[#] Compiling file ./Shader/ShaderType.cpp"
	-$(Compiler) -c "./Shader/ShaderType.cpp" -o $(DirTemp)/ShaderType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Shader.o: ./Shader/Shader.cpp
	@echo "[#] Compiling file ./Shader/Shader.cpp"
	-$(Compiler) -c "./Shader/Shader.cpp" -o $(DirTemp)/Shader.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ShaderProgram.o: ./Shader/ShaderProgram.cpp
	@echo "[#] Compiling file ./Shader/ShaderProgram.cpp"
	-$(Compiler) -c "./Shader/ShaderProgram.cpp" -o $(DirTemp)/ShaderProgram.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Queue.o: ./Container/Queue.hpp
	@echo "[#] Compiling file ./Container/Queue.hpp"
	-$(Compiler) -c "./Container/Queue.hpp" -o $(DirTemp)/Queue.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/DictionaryStatic.o: ./Container/DictionaryStatic.hpp
	@echo "[#] Compiling file ./Container/DictionaryStatic.hpp"
	-$(Compiler) -c "./Container/DictionaryStatic.hpp" -o $(DirTemp)/DictionaryStatic.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/BitStreamHusk.o: ./Container/BitStreamHusk.cpp
	@echo "[#] Compiling file ./Container/BitStreamHusk.cpp"
	-$(Compiler) -c "./Container/BitStreamHusk.cpp" -o $(DirTemp)/BitStreamHusk.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Table.o: ./Container/Table.hpp
	@echo "[#] Compiling file ./Container/Table.hpp"
	-$(Compiler) -c "./Container/Table.hpp" -o $(DirTemp)/Table.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/AsciiString.o: ./Container/AsciiString.cpp
	@echo "[#] Compiling file ./Container/AsciiString.cpp"
	-$(Compiler) -c "./Container/AsciiString.cpp" -o $(DirTemp)/AsciiString.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/LinkedListNode.o: ./Container/LinkedListNode.hpp
	@echo "[#] Compiling file ./Container/LinkedListNode.hpp"
	-$(Compiler) -c "./Container/LinkedListNode.hpp" -o $(DirTemp)/LinkedListNode.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/RingBuffer.o: ./Container/RingBuffer.hpp
	@echo "[#] Compiling file ./Container/RingBuffer.hpp"
	-$(Compiler) -c "./Container/RingBuffer.hpp" -o $(DirTemp)/RingBuffer.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Dictionary.o: ./Container/Dictionary.hpp
	@echo "[#] Compiling file ./Container/Dictionary.hpp"
	-$(Compiler) -c "./Container/Dictionary.hpp" -o $(DirTemp)/Dictionary.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/BinaryTreeNode.o: ./Container/BinaryTree/BinaryTreeNode.hpp
	@echo "[#] Compiling file ./Container/BinaryTree/BinaryTreeNode.hpp"
	-$(Compiler) -c "./Container/BinaryTree/BinaryTreeNode.hpp" -o $(DirTemp)/BinaryTreeNode.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/BinaryTree.o: ./Container/BinaryTree/BinaryTree.hpp
	@echo "[#] Compiling file ./Container/BinaryTree/BinaryTree.hpp"
	-$(Compiler) -c "./Container/BinaryTree/BinaryTree.hpp" -o $(DirTemp)/BinaryTree.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/BinaryTreeData.o: ./Container/BinaryTree/BinaryTreeData.hpp
	@echo "[#] Compiling file ./Container/BinaryTree/BinaryTreeData.hpp"
	-$(Compiler) -c "./Container/BinaryTree/BinaryTreeData.hpp" -o $(DirTemp)/BinaryTreeData.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/List.o: ./Container/List.hpp
	@echo "[#] Compiling file ./Container/List.hpp"
	-$(Compiler) -c "./Container/List.hpp" -o $(DirTemp)/List.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/QuadTreeDirection.o: ./Container/QuadTree/QuadTreeDirection.hpp
	@echo "[#] Compiling file ./Container/QuadTree/QuadTreeDirection.hpp"
	-$(Compiler) -c "./Container/QuadTree/QuadTreeDirection.hpp" -o $(DirTemp)/QuadTreeDirection.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/QuadTreePosition.o: ./Container/QuadTree/QuadTreePosition.hpp
	@echo "[#] Compiling file ./Container/QuadTree/QuadTreePosition.hpp"
	-$(Compiler) -c "./Container/QuadTree/QuadTreePosition.hpp" -o $(DirTemp)/QuadTreePosition.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/QuadTree.o: ./Container/QuadTree/QuadTree.hpp
	@echo "[#] Compiling file ./Container/QuadTree/QuadTree.hpp"
	-$(Compiler) -c "./Container/QuadTree/QuadTree.hpp" -o $(DirTemp)/QuadTree.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/QuadTreeNode.o: ./Container/QuadTree/QuadTreeNode.hpp
	@echo "[#] Compiling file ./Container/QuadTree/QuadTreeNode.hpp"
	-$(Compiler) -c "./Container/QuadTree/QuadTreeNode.hpp" -o $(DirTemp)/QuadTreeNode.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/LinkedList.o: ./Container/LinkedList.hpp
	@echo "[#] Compiling file ./Container/LinkedList.hpp"
	-$(Compiler) -c "./Container/LinkedList.hpp" -o $(DirTemp)/LinkedList.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IFileFormat.o: ./IFileFormat.hpp
	@echo "[#] Compiling file ./IFileFormat.hpp"
	-$(Compiler) -c "./IFileFormat.hpp" -o $(DirTemp)/IFileFormat.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Camera.o: ./Camera/Camera.cpp
	@echo "[#] Compiling file ./Camera/Camera.cpp"
	-$(Compiler) -c "./Camera/Camera.cpp" -o $(DirTemp)/Camera.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/CameraPerspective.o: ./Camera/CameraPerspective.hpp
	@echo "[#] Compiling file ./Camera/CameraPerspective.hpp"
	-$(Compiler) -c "./Camera/CameraPerspective.hpp" -o $(DirTemp)/CameraPerspective.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Image.o: ./Image/Image.cpp
	@echo "[#] Compiling file ./Image/Image.cpp"
	-$(Compiler) -c "./Image/Image.cpp" -o $(DirTemp)/Image.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/BMP.o: ./Image/BMP/BMP.cpp
	@echo "[#] Compiling file ./Image/BMP/BMP.cpp"
	-$(Compiler) -c "./Image/BMP/BMP.cpp" -o $(DirTemp)/BMP.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/BMPInfoHeaderType.o: ./Image/BMP/BMPInfoHeaderType.cpp
	@echo "[#] Compiling file ./Image/BMP/BMPInfoHeaderType.cpp"
	-$(Compiler) -c "./Image/BMP/BMPInfoHeaderType.cpp" -o $(DirTemp)/BMPInfoHeaderType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/BMPType.o: ./Image/BMP/BMPType.cpp
	@echo "[#] Compiling file ./Image/BMP/BMPType.cpp"
	-$(Compiler) -c "./Image/BMP/BMPType.cpp" -o $(DirTemp)/BMPType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/BMPInfoHeader.o: ./Image/BMP/BMPInfoHeader.cpp
	@echo "[#] Compiling file ./Image/BMP/BMPInfoHeader.cpp"
	-$(Compiler) -c "./Image/BMP/BMPInfoHeader.cpp" -o $(DirTemp)/BMPInfoHeader.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TGAImageDataType.o: ./Image/TGA/TGAImageDataType.cpp
	@echo "[#] Compiling file ./Image/TGA/TGAImageDataType.cpp"
	-$(Compiler) -c "./Image/TGA/TGAImageDataType.cpp" -o $(DirTemp)/TGAImageDataType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TGA.o: ./Image/TGA/TGA.cpp
	@echo "[#] Compiling file ./Image/TGA/TGA.cpp"
	-$(Compiler) -c "./Image/TGA/TGA.cpp" -o $(DirTemp)/TGA.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TGABitsPerPixel.o: ./Image/TGA/TGABitsPerPixel.cpp
	@echo "[#] Compiling file ./Image/TGA/TGABitsPerPixel.cpp"
	-$(Compiler) -c "./Image/TGA/TGABitsPerPixel.cpp" -o $(DirTemp)/TGABitsPerPixel.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNG.o: ./Image/PNG/PNG.cpp
	@echo "[#] Compiling file ./Image/PNG/PNG.cpp"
	-$(Compiler) -c "./Image/PNG/PNG.cpp" -o $(DirTemp)/PNG.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGColorCompressor.o: ./Image/PNG/PNGColorCompressor.cpp
	@echo "[#] Compiling file ./Image/PNG/PNGColorCompressor.cpp"
	-$(Compiler) -c "./Image/PNG/PNGColorCompressor.cpp" -o $(DirTemp)/PNGColorCompressor.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGColorTree.o: ./Image/PNG/PNGColorTree.cpp
	@echo "[#] Compiling file ./Image/PNG/PNGColorTree.cpp"
	-$(Compiler) -c "./Image/PNG/PNGColorTree.cpp" -o $(DirTemp)/PNGColorTree.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGTransparency.o: ./Image/PNG/Chunk/PNGTransparency.cpp
	@echo "[#] Compiling file ./Image/PNG/Chunk/PNGTransparency.cpp"
	-$(Compiler) -c "./Image/PNG/Chunk/PNGTransparency.cpp" -o $(DirTemp)/PNGTransparency.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGColorType.o: ./Image/PNG/Chunk/PNGColorType.cpp
	@echo "[#] Compiling file ./Image/PNG/Chunk/PNGColorType.cpp"
	-$(Compiler) -c "./Image/PNG/Chunk/PNGColorType.cpp" -o $(DirTemp)/PNGColorType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGChunk.o: ./Image/PNG/Chunk/PNGChunk.cpp
	@echo "[#] Compiling file ./Image/PNG/Chunk/PNGChunk.cpp"
	-$(Compiler) -c "./Image/PNG/Chunk/PNGChunk.cpp" -o $(DirTemp)/PNGChunk.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGBackgroundColor.o: ./Image/PNG/Chunk/PNGBackgroundColor.cpp
	@echo "[#] Compiling file ./Image/PNG/Chunk/PNGBackgroundColor.cpp"
	-$(Compiler) -c "./Image/PNG/Chunk/PNGBackgroundColor.cpp" -o $(DirTemp)/PNGBackgroundColor.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGChunkType.o: ./Image/PNG/Chunk/PNGChunkType.cpp
	@echo "[#] Compiling file ./Image/PNG/Chunk/PNGChunkType.cpp"
	-$(Compiler) -c "./Image/PNG/Chunk/PNGChunkType.cpp" -o $(DirTemp)/PNGChunkType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGPalette.o: ./Image/PNG/Chunk/PNGPalette.cpp
	@echo "[#] Compiling file ./Image/PNG/Chunk/PNGPalette.cpp"
	-$(Compiler) -c "./Image/PNG/Chunk/PNGPalette.cpp" -o $(DirTemp)/PNGPalette.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGInterlaceMethod.o: ./Image/PNG/Chunk/PNGInterlaceMethod.cpp
	@echo "[#] Compiling file ./Image/PNG/Chunk/PNGInterlaceMethod.cpp"
	-$(Compiler) -c "./Image/PNG/Chunk/PNGInterlaceMethod.cpp" -o $(DirTemp)/PNGInterlaceMethod.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGPrimaryChromatics.o: ./Image/PNG/Chunk/PNGPrimaryChromatics.cpp
	@echo "[#] Compiling file ./Image/PNG/Chunk/PNGPrimaryChromatics.cpp"
	-$(Compiler) -c "./Image/PNG/Chunk/PNGPrimaryChromatics.cpp" -o $(DirTemp)/PNGPrimaryChromatics.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGPhysicalPixelDimension.o: ./Image/PNG/Chunk/PNGPhysicalPixelDimension.cpp
	@echo "[#] Compiling file ./Image/PNG/Chunk/PNGPhysicalPixelDimension.cpp"
	-$(Compiler) -c "./Image/PNG/Chunk/PNGPhysicalPixelDimension.cpp" -o $(DirTemp)/PNGPhysicalPixelDimension.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGSuggestedPalette.o: ./Image/PNG/Chunk/PNGSuggestedPalette.cpp
	@echo "[#] Compiling file ./Image/PNG/Chunk/PNGSuggestedPalette.cpp"
	-$(Compiler) -c "./Image/PNG/Chunk/PNGSuggestedPalette.cpp" -o $(DirTemp)/PNGSuggestedPalette.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGImageHeader.o: ./Image/PNG/Chunk/PNGImageHeader.cpp
	@echo "[#] Compiling file ./Image/PNG/Chunk/PNGImageHeader.cpp"
	-$(Compiler) -c "./Image/PNG/Chunk/PNGImageHeader.cpp" -o $(DirTemp)/PNGImageHeader.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGLastModificationTime.o: ./Image/PNG/Chunk/PNGLastModificationTime.cpp
	@echo "[#] Compiling file ./Image/PNG/Chunk/PNGLastModificationTime.cpp"
	-$(Compiler) -c "./Image/PNG/Chunk/PNGLastModificationTime.cpp" -o $(DirTemp)/PNGLastModificationTime.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGPaletteHistogram.o: ./Image/PNG/Chunk/PNGPaletteHistogram.cpp
	@echo "[#] Compiling file ./Image/PNG/Chunk/PNGPaletteHistogram.cpp"
	-$(Compiler) -c "./Image/PNG/Chunk/PNGPaletteHistogram.cpp" -o $(DirTemp)/PNGPaletteHistogram.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ImageType.o: ./Image/ImageType.cpp
	@echo "[#] Compiling file ./Image/ImageType.cpp"
	-$(Compiler) -c "./Image/ImageType.cpp" -o $(DirTemp)/ImageType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/GIF.o: ./Image/GIF/GIF.cpp
	@echo "[#] Compiling file ./Image/GIF/GIF.cpp"
	-$(Compiler) -c "./Image/GIF/GIF.cpp" -o $(DirTemp)/GIF.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ImageDataFormat.o: ./Image/ImageDataFormat.cpp
	@echo "[#] Compiling file ./Image/ImageDataFormat.cpp"
	-$(Compiler) -c "./Image/ImageDataFormat.cpp" -o $(DirTemp)/ImageDataFormat.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/JPEGHuffmanTable.o: ./Image/JPEG/JPEGHuffmanTable.cpp
	@echo "[#] Compiling file ./Image/JPEG/JPEGHuffmanTable.cpp"
	-$(Compiler) -c "./Image/JPEG/JPEGHuffmanTable.cpp" -o $(DirTemp)/JPEGHuffmanTable.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/JPEGScanSelector.o: ./Image/JPEG/JPEGScanSelector.cpp
	@echo "[#] Compiling file ./Image/JPEG/JPEGScanSelector.cpp"
	-$(Compiler) -c "./Image/JPEG/JPEGScanSelector.cpp" -o $(DirTemp)/JPEGScanSelector.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/JPEGFileInfo.o: ./Image/JPEG/JPEGFileInfo.cpp
	@echo "[#] Compiling file ./Image/JPEG/JPEGFileInfo.cpp"
	-$(Compiler) -c "./Image/JPEG/JPEGFileInfo.cpp" -o $(DirTemp)/JPEGFileInfo.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/JPEG.o: ./Image/JPEG/JPEG.cpp
	@echo "[#] Compiling file ./Image/JPEG/JPEG.cpp"
	-$(Compiler) -c "./Image/JPEG/JPEG.cpp" -o $(DirTemp)/JPEG.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/JPEGFrame.o: ./Image/JPEG/JPEGFrame.cpp
	@echo "[#] Compiling file ./Image/JPEG/JPEGFrame.cpp"
	-$(Compiler) -c "./Image/JPEG/JPEGFrame.cpp" -o $(DirTemp)/JPEGFrame.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/JPEGMarker.o: ./Image/JPEG/JPEGMarker.cpp
	@echo "[#] Compiling file ./Image/JPEG/JPEGMarker.cpp"
	-$(Compiler) -c "./Image/JPEG/JPEGMarker.cpp" -o $(DirTemp)/JPEGMarker.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/JPEGScanStart.o: ./Image/JPEG/JPEGScanStart.cpp
	@echo "[#] Compiling file ./Image/JPEG/JPEGScanStart.cpp"
	-$(Compiler) -c "./Image/JPEG/JPEGScanStart.cpp" -o $(DirTemp)/JPEGScanStart.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/JPEGFrameComponent.o: ./Image/JPEG/JPEGFrameComponent.cpp
	@echo "[#] Compiling file ./Image/JPEG/JPEGFrameComponent.cpp"
	-$(Compiler) -c "./Image/JPEG/JPEGFrameComponent.cpp" -o $(DirTemp)/JPEGFrameComponent.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TIFF.o: ./Image/TIFF/TIFF.cpp
	@echo "[#] Compiling file ./Image/TIFF/TIFF.cpp"
	-$(Compiler) -c "./Image/TIFF/TIFF.cpp" -o $(DirTemp)/TIFF.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ISBN.o: ./Algorithm/ISBN.cpp
	@echo "[#] Compiling file ./Algorithm/ISBN.cpp"
	-$(Compiler) -c "./Algorithm/ISBN.cpp" -o $(DirTemp)/ISBN.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/CRC32.o: ./Algorithm/CRC32.cpp
	@echo "[#] Compiling file ./Algorithm/CRC32.cpp"
	-$(Compiler) -c "./Algorithm/CRC32.cpp" -o $(DirTemp)/CRC32.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Adler32.o: ./Algorithm/Adler32.cpp
	@echo "[#] Compiling file ./Algorithm/Adler32.cpp"
	-$(Compiler) -c "./Algorithm/Adler32.cpp" -o $(DirTemp)/Adler32.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/AsyncLock.o: ./Async/AsyncLock.cpp
	@echo "[#] Compiling file ./Async/AsyncLock.cpp"
	-$(Compiler) -c "./Async/AsyncLock.cpp" -o $(DirTemp)/AsyncLock.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Thread.o: ./Async/Thread.cpp
	@echo "[#] Compiling file ./Async/Thread.cpp"
	-$(Compiler) -c "./Async/Thread.cpp" -o $(DirTemp)/Thread.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ErrorCode.o: ./ErrorCode.cpp
	@echo "[#] Compiling file ./ErrorCode.cpp"
	-$(Compiler) -c "./ErrorCode.cpp" -o $(DirTemp)/ErrorCode.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/UUID.o: ./Types/UUID.cpp
	@echo "[#] Compiling file ./Types/UUID.cpp"
	-$(Compiler) -c "./Types/UUID.cpp" -o $(DirTemp)/UUID.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/StopWatch.o: ./Time/StopWatch.cpp
	@echo "[#] Compiling file ./Time/StopWatch.cpp"
	-$(Compiler) -c "./Time/StopWatch.cpp" -o $(DirTemp)/StopWatch.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/SocketActionResult.o: ./Network/SocketActionResult.cpp
	@echo "[#] Compiling file ./Network/SocketActionResult.cpp"
	-$(Compiler) -c "./Network/SocketActionResult.cpp" -o $(DirTemp)/SocketActionResult.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IClientListener.o: ./Network/IClientListener.hpp
	@echo "[#] Compiling file ./Network/IClientListener.hpp"
	-$(Compiler) -c "./Network/IClientListener.hpp" -o $(DirTemp)/IClientListener.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Client.o: ./Network/Client.cpp
	@echo "[#] Compiling file ./Network/Client.cpp"
	-$(Compiler) -c "./Network/Client.cpp" -o $(DirTemp)/Client.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ProtocolMode.o: ./Network/ProtocolMode.cpp
	@echo "[#] Compiling file ./Network/ProtocolMode.cpp"
	-$(Compiler) -c "./Network/ProtocolMode.cpp" -o $(DirTemp)/ProtocolMode.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IPAdressInfo.o: ./Network/IPAdressInfo.cpp
	@echo "[#] Compiling file ./Network/IPAdressInfo.cpp"
	-$(Compiler) -c "./Network/IPAdressInfo.cpp" -o $(DirTemp)/IPAdressInfo.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ServerListeningThreadInfo.o: ./Network/ServerListeningThreadInfo.cpp
	@echo "[#] Compiling file ./Network/ServerListeningThreadInfo.cpp"
	-$(Compiler) -c "./Network/ServerListeningThreadInfo.cpp" -o $(DirTemp)/ServerListeningThreadInfo.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IOSocket.o: ./Network/IOSocket.cpp
	@echo "[#] Compiling file ./Network/IOSocket.cpp"
	-$(Compiler) -c "./Network/IOSocket.cpp" -o $(DirTemp)/IOSocket.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Server.o: ./Network/Server.cpp
	@echo "[#] Compiling file ./Network/Server.cpp"
	-$(Compiler) -c "./Network/Server.cpp" -o $(DirTemp)/Server.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IOSocketMessage.o: ./Network/IOSocketMessage.cpp
	@echo "[#] Compiling file ./Network/IOSocketMessage.cpp"
	-$(Compiler) -c "./Network/IOSocketMessage.cpp" -o $(DirTemp)/IOSocketMessage.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/SocketType.o: ./Network/SocketType.cpp
	@echo "[#] Compiling file ./Network/SocketType.cpp"
	-$(Compiler) -c "./Network/SocketType.cpp" -o $(DirTemp)/SocketType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IPVersion.o: ./Network/IPVersion.cpp
	@echo "[#] Compiling file ./Network/IPVersion.cpp"
	-$(Compiler) -c "./Network/IPVersion.cpp" -o $(DirTemp)/IPVersion.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IPAdressFamily.o: ./Network/IPAdressFamily.cpp
	@echo "[#] Compiling file ./Network/IPAdressFamily.cpp"
	-$(Compiler) -c "./Network/IPAdressFamily.cpp" -o $(DirTemp)/IPAdressFamily.o
#-------------------------------------------------------------------------------------------------
$(DirExport)/ExportLib: $(DirTemp)/Resource.o $(DirTemp)/Math.o $(DirTemp)/Interpolate.o $(DirTemp)/BoxPlot.o $(DirTemp)/Vector4.o $(DirTemp)/AngleRadians.o $(DirTemp)/Vector3.o $(DirTemp)/Matrix3x3.o $(DirTemp)/Cylinder.o $(DirTemp)/SquarePyramid.o $(DirTemp)/Cuboid.o $(DirTemp)/Sphere.o $(DirTemp)/Icosahedron.o $(DirTemp)/Cone.o $(DirTemp)/Form.o $(DirTemp)/Cube.o $(DirTemp)/Matrix4x4.o $(DirTemp)/Rectangle.o $(DirTemp)/Triangle.o $(DirTemp)/Pentagon.o $(DirTemp)/Circle.o $(DirTemp)/Shape.o $(DirTemp)/Square.o $(DirTemp)/Star.o $(DirTemp)/Hexagon.o $(DirTemp)/Matrix.o $(DirTemp)/Padding.o $(DirTemp)/Vector2.o $(DirTemp)/Matrix2x2.o $(DirTemp)/AngleDegree.o $(DirTemp)/PhysicsStatic.o $(DirTemp)/GravitySphere.o $(DirTemp)/PhysicsDynamic.o $(DirTemp)/Collider.o $(DirTemp)/GravityField.o $(DirTemp)/GravityCube.o $(DirTemp)/MP3ChannelMode.o $(DirTemp)/MP3MPEGVersion.o $(DirTemp)/MPEGGenre.o $(DirTemp)/MP3Layer.o $(DirTemp)/MP3.o $(DirTemp)/MP3Emphasis.o $(DirTemp)/MP3Header.o $(DirTemp)/MPEGGenre.o $(DirTemp)/MPEGAudioTag.o $(DirTemp)/SoundPlayStyle.o $(DirTemp)/FMT.o $(DirTemp)/RIFF.o $(DirTemp)/WAV.o $(DirTemp)/M4A.o $(DirTemp)/Sound.o $(DirTemp)/WMA.o $(DirTemp)/OGG.o $(DirTemp)/FLAC.o $(DirTemp)/MIDITrackHeader.o $(DirTemp)/MIDICommandExtended.o $(DirTemp)/MID.o $(DirTemp)/MIDINote.o $(DirTemp)/MIDICommand.o $(DirTemp)/MIDITrack.o $(DirTemp)/AAC.o $(DirTemp)/ISoundFormat.o $(DirTemp)/ICypher.o $(DirTemp)/RSA.o $(DirTemp)/Caesar.o $(DirTemp)/ResourceType.o $(DirTemp)/Video.o $(DirTemp)/MP4.o $(DirTemp)/IVideoFormat.o $(DirTemp)/AVI.o $(DirTemp)/AVIHeader.o $(DirTemp)/Dialog.o $(DirTemp)/FNTCharacter.o $(DirTemp)/FNTInfo.o $(DirTemp)/FNTPage.o $(DirTemp)/FNT.o $(DirTemp)/FNTCommonData.o $(DirTemp)/IFontFormat.o $(DirTemp)/OTF.o $(DirTemp)/Font.o $(DirTemp)/TTF.o $(DirTemp)/TTFTableEntry.o $(DirTemp)/TTFVersion.o $(DirTemp)/TTFHeader.o $(DirTemp)/EncodingID.o $(DirTemp)/PlatformID.o $(DirTemp)/TTFCharacterMapping.o $(DirTemp)/EncodingRecord.o $(DirTemp)/TTFOffsetTable.o $(DirTemp)/TTFVersionType.o $(DirTemp)/TTFCompatibility.o $(DirTemp)/TTFLetterform.o $(DirTemp)/TTFContrast.o $(DirTemp)/TTFMidline.o $(DirTemp)/TTFPanose.o $(DirTemp)/TTFArmStyle.o $(DirTemp)/TTFProportion.o $(DirTemp)/TTFWeight.o $(DirTemp)/TTFHeightX.o $(DirTemp)/TTFSerifStyle.o $(DirTemp)/TTFStrokeVariatoon.o $(DirTemp)/TTFFamilyType.o $(DirTemp)/TTFHorizontalHeader.o $(DirTemp)/TTFKerning.o $(DirTemp)/TTFSubtableFormat0.o $(DirTemp)/TTFKerningSubtable.o $(DirTemp)/TTFSubtableFormat2.o $(DirTemp)/TTFKerningPair.o $(DirTemp)/TTFPostScript.o $(DirTemp)/TTFMaximumProfile.o $(DirTemp)/TTFLinearThreshold.o $(DirTemp)/TTFDigitalSignatureBlock.o $(DirTemp)/TTFDigitalSignatureRecord.o $(DirTemp)/TTFDigitalSignature.o $(DirTemp)/TTFVerticalDeviceMetrics.o $(DirTemp)/TTFTableEntryType.o $(DirTemp)/Event.o $(DirTemp)/FBX.o $(DirTemp)/Material.o $(DirTemp)/Model.o $(DirTemp)/MeshStructure.o $(DirTemp)/A3DS.o $(DirTemp)/Mesh.o $(DirTemp)/IModelFormat.o $(DirTemp)/MeshRenderInfo.o $(DirTemp)/Vertex.o $(DirTemp)/WRL.o $(DirTemp)/LinkedMesh.o $(DirTemp)/STL.o $(DirTemp)/PLY.o $(DirTemp)/OBJ.o $(DirTemp)/MTL.o $(DirTemp)/OBJElement.o $(DirTemp)/MeshIndexData.o $(DirTemp)/HTTPServer.o $(DirTemp)/HTTPError.o $(DirTemp)/HTTPRequestMethod.o $(DirTemp)/ADAM7.o $(DirTemp)/ZLIB.o $(DirTemp)/ZLIBHeader.o $(DirTemp)/ZLIBCompressionMethod.o $(DirTemp)/ZLIBCompressionLevel.o $(DirTemp)/HuffmanCodeType.o $(DirTemp)/HuffmanTree.o $(DirTemp)/HuffmanSymbol.o $(DirTemp)/HuffmanNumberCode.o $(DirTemp)/DeflateBlock.o $(DirTemp)/DeflateEncodingMethod.o $(DirTemp)/Bash.o $(DirTemp)/FileStream.o $(DirTemp)/ProgramExecuteResultListener.o $(DirTemp)/FileOpenMode.o $(DirTemp)/ProgramExecuteInfo.o $(DirTemp)/ByteStream.o $(DirTemp)/FilePersistence.o $(DirTemp)/IFIle.o $(DirTemp)/FileTemporary.o $(DirTemp)/FileActionResult.o $(DirTemp)/OpenFileDialog.o $(DirTemp)/Program.o $(DirTemp)/File.o $(DirTemp)/Level.o $(DirTemp)/SkyBox.o $(DirTemp)/Sprite.o $(DirTemp)/EML.o $(DirTemp)/ShaderType.o $(DirTemp)/Shader.o $(DirTemp)/ShaderProgram.o $(DirTemp)/Queue.o $(DirTemp)/DictionaryStatic.o $(DirTemp)/BitStreamHusk.o $(DirTemp)/Table.o $(DirTemp)/AsciiString.o $(DirTemp)/LinkedListNode.o $(DirTemp)/RingBuffer.o $(DirTemp)/Dictionary.o $(DirTemp)/BinaryTreeNode.o $(DirTemp)/BinaryTree.o $(DirTemp)/BinaryTreeData.o $(DirTemp)/List.o $(DirTemp)/QuadTreeDirection.o $(DirTemp)/QuadTreePosition.o $(DirTemp)/QuadTree.o $(DirTemp)/QuadTreeNode.o $(DirTemp)/LinkedList.o $(DirTemp)/IFileFormat.o $(DirTemp)/Camera.o $(DirTemp)/CameraPerspective.o $(DirTemp)/Image.o $(DirTemp)/BMP.o $(DirTemp)/BMPInfoHeaderType.o $(DirTemp)/BMPType.o $(DirTemp)/BMPInfoHeader.o $(DirTemp)/TGAImageDataType.o $(DirTemp)/TGA.o $(DirTemp)/TGABitsPerPixel.o $(DirTemp)/PNG.o $(DirTemp)/PNGColorCompressor.o $(DirTemp)/PNGColorTree.o $(DirTemp)/PNGTransparency.o $(DirTemp)/PNGColorType.o $(DirTemp)/PNGChunk.o $(DirTemp)/PNGBackgroundColor.o $(DirTemp)/PNGChunkType.o $(DirTemp)/PNGPalette.o $(DirTemp)/PNGInterlaceMethod.o $(DirTemp)/PNGPrimaryChromatics.o $(DirTemp)/PNGPhysicalPixelDimension.o $(DirTemp)/PNGSuggestedPalette.o $(DirTemp)/PNGImageHeader.o $(DirTemp)/PNGLastModificationTime.o $(DirTemp)/PNGPaletteHistogram.o $(DirTemp)/ImageType.o $(DirTemp)/GIF.o $(DirTemp)/ImageDataFormat.o $(DirTemp)/JPEGHuffmanTable.o $(DirTemp)/JPEGScanSelector.o $(DirTemp)/JPEGFileInfo.o $(DirTemp)/JPEG.o $(DirTemp)/JPEGFrame.o $(DirTemp)/JPEGMarker.o $(DirTemp)/JPEGScanStart.o $(DirTemp)/JPEGFrameComponent.o $(DirTemp)/TIFF.o $(DirTemp)/ISBN.o $(DirTemp)/CRC32.o $(DirTemp)/Adler32.o $(DirTemp)/AsyncLock.o $(DirTemp)/Thread.o $(DirTemp)/ErrorCode.o $(DirTemp)/UUID.o $(DirTemp)/StopWatch.o $(DirTemp)/SocketActionResult.o $(DirTemp)/IClientListener.o $(DirTemp)/Client.o $(DirTemp)/ProtocolMode.o $(DirTemp)/IPAdressInfo.o $(DirTemp)/ServerListeningThreadInfo.o $(DirTemp)/IOSocket.o $(DirTemp)/Server.o $(DirTemp)/IOSocketMessage.o $(DirTemp)/SocketType.o $(DirTemp)/IPVersion.o $(DirTemp)/IPAdressFamily.o 
	ar rcs $(DirExport)/ExportLib.lib $(DirTemp)/Resource.o $(DirTemp)/Math.o $(DirTemp)/Interpolate.o $(DirTemp)/BoxPlot.o $(DirTemp)/Vector4.o $(DirTemp)/AngleRadians.o $(DirTemp)/Vector3.o $(DirTemp)/Matrix3x3.o $(DirTemp)/Cylinder.o $(DirTemp)/SquarePyramid.o $(DirTemp)/Cuboid.o $(DirTemp)/Sphere.o $(DirTemp)/Icosahedron.o $(DirTemp)/Cone.o $(DirTemp)/Form.o $(DirTemp)/Cube.o $(DirTemp)/Matrix4x4.o $(DirTemp)/Rectangle.o $(DirTemp)/Triangle.o $(DirTemp)/Pentagon.o $(DirTemp)/Circle.o $(DirTemp)/Shape.o $(DirTemp)/Square.o $(DirTemp)/Star.o $(DirTemp)/Hexagon.o $(DirTemp)/Matrix.o $(DirTemp)/Padding.o $(DirTemp)/Vector2.o $(DirTemp)/Matrix2x2.o $(DirTemp)/AngleDegree.o $(DirTemp)/PhysicsStatic.o $(DirTemp)/GravitySphere.o $(DirTemp)/PhysicsDynamic.o $(DirTemp)/Collider.o $(DirTemp)/GravityField.o $(DirTemp)/GravityCube.o $(DirTemp)/MP3ChannelMode.o $(DirTemp)/MP3MPEGVersion.o $(DirTemp)/MPEGGenre.o $(DirTemp)/MP3Layer.o $(DirTemp)/MP3.o $(DirTemp)/MP3Emphasis.o $(DirTemp)/MP3Header.o $(DirTemp)/MPEGGenre.o $(DirTemp)/MPEGAudioTag.o $(DirTemp)/SoundPlayStyle.o $(DirTemp)/FMT.o $(DirTemp)/RIFF.o $(DirTemp)/WAV.o $(DirTemp)/M4A.o $(DirTemp)/Sound.o $(DirTemp)/WMA.o $(DirTemp)/OGG.o $(DirTemp)/FLAC.o $(DirTemp)/MIDITrackHeader.o $(DirTemp)/MIDICommandExtended.o $(DirTemp)/MID.o $(DirTemp)/MIDINote.o $(DirTemp)/MIDICommand.o $(DirTemp)/MIDITrack.o $(DirTemp)/AAC.o $(DirTemp)/ISoundFormat.o $(DirTemp)/ICypher.o $(DirTemp)/RSA.o $(DirTemp)/Caesar.o $(DirTemp)/ResourceType.o $(DirTemp)/Video.o $(DirTemp)/MP4.o $(DirTemp)/IVideoFormat.o $(DirTemp)/AVI.o $(DirTemp)/AVIHeader.o $(DirTemp)/Dialog.o $(DirTemp)/FNTCharacter.o $(DirTemp)/FNTInfo.o $(DirTemp)/FNTPage.o $(DirTemp)/FNT.o $(DirTemp)/FNTCommonData.o $(DirTemp)/IFontFormat.o $(DirTemp)/OTF.o $(DirTemp)/Font.o $(DirTemp)/TTF.o $(DirTemp)/TTFTableEntry.o $(DirTemp)/TTFVersion.o $(DirTemp)/TTFHeader.o $(DirTemp)/EncodingID.o $(DirTemp)/PlatformID.o $(DirTemp)/TTFCharacterMapping.o $(DirTemp)/EncodingRecord.o $(DirTemp)/TTFOffsetTable.o $(DirTemp)/TTFVersionType.o $(DirTemp)/TTFCompatibility.o $(DirTemp)/TTFLetterform.o $(DirTemp)/TTFContrast.o $(DirTemp)/TTFMidline.o $(DirTemp)/TTFPanose.o $(DirTemp)/TTFArmStyle.o $(DirTemp)/TTFProportion.o $(DirTemp)/TTFWeight.o $(DirTemp)/TTFHeightX.o $(DirTemp)/TTFSerifStyle.o $(DirTemp)/TTFStrokeVariatoon.o $(DirTemp)/TTFFamilyType.o $(DirTemp)/TTFHorizontalHeader.o $(DirTemp)/TTFKerning.o $(DirTemp)/TTFSubtableFormat0.o $(DirTemp)/TTFKerningSubtable.o $(DirTemp)/TTFSubtableFormat2.o $(DirTemp)/TTFKerningPair.o $(DirTemp)/TTFPostScript.o $(DirTemp)/TTFMaximumProfile.o $(DirTemp)/TTFLinearThreshold.o $(DirTemp)/TTFDigitalSignatureBlock.o $(DirTemp)/TTFDigitalSignatureRecord.o $(DirTemp)/TTFDigitalSignature.o $(DirTemp)/TTFVerticalDeviceMetrics.o $(DirTemp)/TTFTableEntryType.o $(DirTemp)/Event.o $(DirTemp)/FBX.o $(DirTemp)/Material.o $(DirTemp)/Model.o $(DirTemp)/MeshStructure.o $(DirTemp)/A3DS.o $(DirTemp)/Mesh.o $(DirTemp)/IModelFormat.o $(DirTemp)/MeshRenderInfo.o $(DirTemp)/Vertex.o $(DirTemp)/WRL.o $(DirTemp)/LinkedMesh.o $(DirTemp)/STL.o $(DirTemp)/PLY.o $(DirTemp)/OBJ.o $(DirTemp)/MTL.o $(DirTemp)/OBJElement.o $(DirTemp)/MeshIndexData.o $(DirTemp)/HTTPServer.o $(DirTemp)/HTTPError.o $(DirTemp)/HTTPRequestMethod.o $(DirTemp)/ADAM7.o $(DirTemp)/ZLIB.o $(DirTemp)/ZLIBHeader.o $(DirTemp)/ZLIBCompressionMethod.o $(DirTemp)/ZLIBCompressionLevel.o $(DirTemp)/HuffmanCodeType.o $(DirTemp)/HuffmanTree.o $(DirTemp)/HuffmanSymbol.o $(DirTemp)/HuffmanNumberCode.o $(DirTemp)/DeflateBlock.o $(DirTemp)/DeflateEncodingMethod.o $(DirTemp)/Bash.o $(DirTemp)/FileStream.o $(DirTemp)/ProgramExecuteResultListener.o $(DirTemp)/FileOpenMode.o $(DirTemp)/ProgramExecuteInfo.o $(DirTemp)/ByteStream.o $(DirTemp)/FilePersistence.o $(DirTemp)/IFIle.o $(DirTemp)/FileTemporary.o $(DirTemp)/FileActionResult.o $(DirTemp)/OpenFileDialog.o $(DirTemp)/Program.o $(DirTemp)/File.o $(DirTemp)/Level.o $(DirTemp)/SkyBox.o $(DirTemp)/Sprite.o $(DirTemp)/EML.o $(DirTemp)/ShaderType.o $(DirTemp)/Shader.o $(DirTemp)/ShaderProgram.o $(DirTemp)/Queue.o $(DirTemp)/DictionaryStatic.o $(DirTemp)/BitStreamHusk.o $(DirTemp)/Table.o $(DirTemp)/AsciiString.o $(DirTemp)/LinkedListNode.o $(DirTemp)/RingBuffer.o $(DirTemp)/Dictionary.o $(DirTemp)/BinaryTreeNode.o $(DirTemp)/BinaryTree.o $(DirTemp)/BinaryTreeData.o $(DirTemp)/List.o $(DirTemp)/QuadTreeDirection.o $(DirTemp)/QuadTreePosition.o $(DirTemp)/QuadTree.o $(DirTemp)/QuadTreeNode.o $(DirTemp)/LinkedList.o $(DirTemp)/IFileFormat.o $(DirTemp)/Camera.o $(DirTemp)/CameraPerspective.o $(DirTemp)/Image.o $(DirTemp)/BMP.o $(DirTemp)/BMPInfoHeaderType.o $(DirTemp)/BMPType.o $(DirTemp)/BMPInfoHeader.o $(DirTemp)/TGAImageDataType.o $(DirTemp)/TGA.o $(DirTemp)/TGABitsPerPixel.o $(DirTemp)/PNG.o $(DirTemp)/PNGColorCompressor.o $(DirTemp)/PNGColorTree.o $(DirTemp)/PNGTransparency.o $(DirTemp)/PNGColorType.o $(DirTemp)/PNGChunk.o $(DirTemp)/PNGBackgroundColor.o $(DirTemp)/PNGChunkType.o $(DirTemp)/PNGPalette.o $(DirTemp)/PNGInterlaceMethod.o $(DirTemp)/PNGPrimaryChromatics.o $(DirTemp)/PNGPhysicalPixelDimension.o $(DirTemp)/PNGSuggestedPalette.o $(DirTemp)/PNGImageHeader.o $(DirTemp)/PNGLastModificationTime.o $(DirTemp)/PNGPaletteHistogram.o $(DirTemp)/ImageType.o $(DirTemp)/GIF.o $(DirTemp)/ImageDataFormat.o $(DirTemp)/JPEGHuffmanTable.o $(DirTemp)/JPEGScanSelector.o $(DirTemp)/JPEGFileInfo.o $(DirTemp)/JPEG.o $(DirTemp)/JPEGFrame.o $(DirTemp)/JPEGMarker.o $(DirTemp)/JPEGScanStart.o $(DirTemp)/JPEGFrameComponent.o $(DirTemp)/TIFF.o $(DirTemp)/ISBN.o $(DirTemp)/CRC32.o $(DirTemp)/Adler32.o $(DirTemp)/AsyncLock.o $(DirTemp)/Thread.o $(DirTemp)/ErrorCode.o $(DirTemp)/UUID.o $(DirTemp)/StopWatch.o $(DirTemp)/SocketActionResult.o $(DirTemp)/IClientListener.o $(DirTemp)/Client.o $(DirTemp)/ProtocolMode.o $(DirTemp)/IPAdressInfo.o $(DirTemp)/ServerListeningThreadInfo.o $(DirTemp)/IOSocket.o $(DirTemp)/Server.o $(DirTemp)/IOSocketMessage.o $(DirTemp)/SocketType.o $(DirTemp)/IPVersion.o $(DirTemp)/IPAdressFamily.o 
#-------------------------------------------------------------------------------------------------
#########################################
