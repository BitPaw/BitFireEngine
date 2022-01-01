#######################################
# MakeFile Generator - BitFire Engine #
#######################################
#-------------------------------------------------------------------------------------------------
bin/Resource.cpp.o: ./Source/Resource.cpp
	@echo [#] Compiling file ./Source/Resource.cpp
	g++ -c ./Source/Resource.cpp
#-------------------------------------------------------------------------------------------------
bin/Math.cpp.o: ./Source/Math/Math.cpp
	@echo [#] Compiling file ./Source/Math/Math.cpp
	g++ -c ./Source/Math/Math.cpp
#-------------------------------------------------------------------------------------------------
bin/Interpolate.cpp.o: ./Source/Math/Interpolate.cpp
	@echo [#] Compiling file ./Source/Math/Interpolate.cpp
	g++ -c ./Source/Math/Interpolate.cpp
#-------------------------------------------------------------------------------------------------
bin/BoxPlot.hpp.o: ./Source/Math/Diagrams/BoxPlot.hpp
	@echo [#] Compiling file ./Source/Math/Diagrams/BoxPlot.hpp
	g++ -c ./Source/Math/Diagrams/BoxPlot.hpp
#-------------------------------------------------------------------------------------------------
bin/Vector4.hpp.o: ./Source/Math/Geometry/Vector4.hpp
	@echo [#] Compiling file ./Source/Math/Geometry/Vector4.hpp
	g++ -c ./Source/Math/Geometry/Vector4.hpp
#-------------------------------------------------------------------------------------------------
bin/AngleRadians.hpp.o: ./Source/Math/Geometry/AngleRadians.hpp
	@echo [#] Compiling file ./Source/Math/Geometry/AngleRadians.hpp
	g++ -c ./Source/Math/Geometry/AngleRadians.hpp
#-------------------------------------------------------------------------------------------------
bin/Vector3.hpp.o: ./Source/Math/Geometry/Vector3.hpp
	@echo [#] Compiling file ./Source/Math/Geometry/Vector3.hpp
	g++ -c ./Source/Math/Geometry/Vector3.hpp
#-------------------------------------------------------------------------------------------------
bin/Matrix3x3.hpp.o: ./Source/Math/Geometry/Matrix3x3.hpp
	@echo [#] Compiling file ./Source/Math/Geometry/Matrix3x3.hpp
	g++ -c ./Source/Math/Geometry/Matrix3x3.hpp
#-------------------------------------------------------------------------------------------------
bin/Cylinder.cpp.o: ./Source/Math/Geometry/Form/Cylinder.cpp
	@echo [#] Compiling file ./Source/Math/Geometry/Form/Cylinder.cpp
	g++ -c ./Source/Math/Geometry/Form/Cylinder.cpp
#-------------------------------------------------------------------------------------------------
bin/SquarePyramid.cpp.o: ./Source/Math/Geometry/Form/SquarePyramid.cpp
	@echo [#] Compiling file ./Source/Math/Geometry/Form/SquarePyramid.cpp
	g++ -c ./Source/Math/Geometry/Form/SquarePyramid.cpp
#-------------------------------------------------------------------------------------------------
bin/Cuboid.cpp.o: ./Source/Math/Geometry/Form/Cuboid.cpp
	@echo [#] Compiling file ./Source/Math/Geometry/Form/Cuboid.cpp
	g++ -c ./Source/Math/Geometry/Form/Cuboid.cpp
#-------------------------------------------------------------------------------------------------
bin/Sphere.cpp.o: ./Source/Math/Geometry/Form/Sphere.cpp
	@echo [#] Compiling file ./Source/Math/Geometry/Form/Sphere.cpp
	g++ -c ./Source/Math/Geometry/Form/Sphere.cpp
#-------------------------------------------------------------------------------------------------
bin/Icosahedron.cpp.o: ./Source/Math/Geometry/Form/Icosahedron.cpp
	@echo [#] Compiling file ./Source/Math/Geometry/Form/Icosahedron.cpp
	g++ -c ./Source/Math/Geometry/Form/Icosahedron.cpp
#-------------------------------------------------------------------------------------------------
bin/Cone.cpp.o: ./Source/Math/Geometry/Form/Cone.cpp
	@echo [#] Compiling file ./Source/Math/Geometry/Form/Cone.cpp
	g++ -c ./Source/Math/Geometry/Form/Cone.cpp
#-------------------------------------------------------------------------------------------------
bin/Form.cpp.o: ./Source/Math/Geometry/Form/Form.cpp
	@echo [#] Compiling file ./Source/Math/Geometry/Form/Form.cpp
	g++ -c ./Source/Math/Geometry/Form/Form.cpp
#-------------------------------------------------------------------------------------------------
bin/Cube.cpp.o: ./Source/Math/Geometry/Form/Cube.cpp
	@echo [#] Compiling file ./Source/Math/Geometry/Form/Cube.cpp
	g++ -c ./Source/Math/Geometry/Form/Cube.cpp
#-------------------------------------------------------------------------------------------------
bin/Matrix4x4.hpp.o: ./Source/Math/Geometry/Matrix4x4.hpp
	@echo [#] Compiling file ./Source/Math/Geometry/Matrix4x4.hpp
	g++ -c ./Source/Math/Geometry/Matrix4x4.hpp
#-------------------------------------------------------------------------------------------------
bin/Rectangle.cpp.o: ./Source/Math/Geometry/Shape/Rectangle.cpp
	@echo [#] Compiling file ./Source/Math/Geometry/Shape/Rectangle.cpp
	g++ -c ./Source/Math/Geometry/Shape/Rectangle.cpp
#-------------------------------------------------------------------------------------------------
bin/Triangle.cpp.o: ./Source/Math/Geometry/Shape/Triangle.cpp
	@echo [#] Compiling file ./Source/Math/Geometry/Shape/Triangle.cpp
	g++ -c ./Source/Math/Geometry/Shape/Triangle.cpp
#-------------------------------------------------------------------------------------------------
bin/Pentagon.cpp.o: ./Source/Math/Geometry/Shape/Pentagon.cpp
	@echo [#] Compiling file ./Source/Math/Geometry/Shape/Pentagon.cpp
	g++ -c ./Source/Math/Geometry/Shape/Pentagon.cpp
#-------------------------------------------------------------------------------------------------
bin/Circle.cpp.o: ./Source/Math/Geometry/Shape/Circle.cpp
	@echo [#] Compiling file ./Source/Math/Geometry/Shape/Circle.cpp
	g++ -c ./Source/Math/Geometry/Shape/Circle.cpp
#-------------------------------------------------------------------------------------------------
bin/Shape.cpp.o: ./Source/Math/Geometry/Shape/Shape.cpp
	@echo [#] Compiling file ./Source/Math/Geometry/Shape/Shape.cpp
	g++ -c ./Source/Math/Geometry/Shape/Shape.cpp
#-------------------------------------------------------------------------------------------------
bin/Square.cpp.o: ./Source/Math/Geometry/Shape/Square.cpp
	@echo [#] Compiling file ./Source/Math/Geometry/Shape/Square.cpp
	g++ -c ./Source/Math/Geometry/Shape/Square.cpp
#-------------------------------------------------------------------------------------------------
bin/Star.cpp.o: ./Source/Math/Geometry/Shape/Star.cpp
	@echo [#] Compiling file ./Source/Math/Geometry/Shape/Star.cpp
	g++ -c ./Source/Math/Geometry/Shape/Star.cpp
#-------------------------------------------------------------------------------------------------
bin/Hexagon.cpp.o: ./Source/Math/Geometry/Shape/Hexagon.cpp
	@echo [#] Compiling file ./Source/Math/Geometry/Shape/Hexagon.cpp
	g++ -c ./Source/Math/Geometry/Shape/Hexagon.cpp
#-------------------------------------------------------------------------------------------------
bin/Matrix.hpp.o: ./Source/Math/Geometry/Matrix.hpp
	@echo [#] Compiling file ./Source/Math/Geometry/Matrix.hpp
	g++ -c ./Source/Math/Geometry/Matrix.hpp
#-------------------------------------------------------------------------------------------------
bin/Padding.hpp.o: ./Source/Math/Geometry/Padding.hpp
	@echo [#] Compiling file ./Source/Math/Geometry/Padding.hpp
	g++ -c ./Source/Math/Geometry/Padding.hpp
#-------------------------------------------------------------------------------------------------
bin/Vector2.hpp.o: ./Source/Math/Geometry/Vector2.hpp
	@echo [#] Compiling file ./Source/Math/Geometry/Vector2.hpp
	g++ -c ./Source/Math/Geometry/Vector2.hpp
#-------------------------------------------------------------------------------------------------
bin/Matrix2x2.hpp.o: ./Source/Math/Geometry/Matrix2x2.hpp
	@echo [#] Compiling file ./Source/Math/Geometry/Matrix2x2.hpp
	g++ -c ./Source/Math/Geometry/Matrix2x2.hpp
#-------------------------------------------------------------------------------------------------
bin/AngleDegree.hpp.o: ./Source/Math/Geometry/AngleDegree.hpp
	@echo [#] Compiling file ./Source/Math/Geometry/AngleDegree.hpp
	g++ -c ./Source/Math/Geometry/AngleDegree.hpp
#-------------------------------------------------------------------------------------------------
bin/PhysicsStatic.hpp.o: ./Source/Math/Physic/PhysicsStatic.hpp
	@echo [#] Compiling file ./Source/Math/Physic/PhysicsStatic.hpp
	g++ -c ./Source/Math/Physic/PhysicsStatic.hpp
#-------------------------------------------------------------------------------------------------
bin/GravitySphere.cpp.o: ./Source/Math/Physic/GravitySphere.cpp
	@echo [#] Compiling file ./Source/Math/Physic/GravitySphere.cpp
	g++ -c ./Source/Math/Physic/GravitySphere.cpp
#-------------------------------------------------------------------------------------------------
bin/PhysicsDynamic.hpp.o: ./Source/Math/Physic/PhysicsDynamic.hpp
	@echo [#] Compiling file ./Source/Math/Physic/PhysicsDynamic.hpp
	g++ -c ./Source/Math/Physic/PhysicsDynamic.hpp
#-------------------------------------------------------------------------------------------------
bin/Collider.cpp.o: ./Source/Math/Physic/Collider.cpp
	@echo [#] Compiling file ./Source/Math/Physic/Collider.cpp
	g++ -c ./Source/Math/Physic/Collider.cpp
#-------------------------------------------------------------------------------------------------
bin/GravityField.cpp.o: ./Source/Math/Physic/GravityField.cpp
	@echo [#] Compiling file ./Source/Math/Physic/GravityField.cpp
	g++ -c ./Source/Math/Physic/GravityField.cpp
#-------------------------------------------------------------------------------------------------
bin/GravityCube.cpp.o: ./Source/Math/Physic/GravityCube.cpp
	@echo [#] Compiling file ./Source/Math/Physic/GravityCube.cpp
	g++ -c ./Source/Math/Physic/GravityCube.cpp
#-------------------------------------------------------------------------------------------------
bin/MP3ChannelMode.hpp.o: ./Source/Sound/MP3/MP3ChannelMode.hpp
	@echo [#] Compiling file ./Source/Sound/MP3/MP3ChannelMode.hpp
	g++ -c ./Source/Sound/MP3/MP3ChannelMode.hpp
#-------------------------------------------------------------------------------------------------
bin/MP3MPEGVersion.hpp.o: ./Source/Sound/MP3/MP3MPEGVersion.hpp
	@echo [#] Compiling file ./Source/Sound/MP3/MP3MPEGVersion.hpp
	g++ -c ./Source/Sound/MP3/MP3MPEGVersion.hpp
#-------------------------------------------------------------------------------------------------
bin/MPEGGenre.cpp.o: ./Source/Sound/MP3/MPEGGenre.cpp
	@echo [#] Compiling file ./Source/Sound/MP3/MPEGGenre.cpp
	g++ -c ./Source/Sound/MP3/MPEGGenre.cpp
#-------------------------------------------------------------------------------------------------
bin/MP3Layer.hpp.o: ./Source/Sound/MP3/MP3Layer.hpp
	@echo [#] Compiling file ./Source/Sound/MP3/MP3Layer.hpp
	g++ -c ./Source/Sound/MP3/MP3Layer.hpp
#-------------------------------------------------------------------------------------------------
bin/MP3.cpp.o: ./Source/Sound/MP3/MP3.cpp
	@echo [#] Compiling file ./Source/Sound/MP3/MP3.cpp
	g++ -c ./Source/Sound/MP3/MP3.cpp
#-------------------------------------------------------------------------------------------------
bin/MP3Emphasis.hpp.o: ./Source/Sound/MP3/MP3Emphasis.hpp
	@echo [#] Compiling file ./Source/Sound/MP3/MP3Emphasis.hpp
	g++ -c ./Source/Sound/MP3/MP3Emphasis.hpp
#-------------------------------------------------------------------------------------------------
bin/MP3Header.cpp.o: ./Source/Sound/MP3/MP3Header.cpp
	@echo [#] Compiling file ./Source/Sound/MP3/MP3Header.cpp
	g++ -c ./Source/Sound/MP3/MP3Header.cpp
#-------------------------------------------------------------------------------------------------
bin/MPEGGenre.hpp.o: ./Source/Sound/MP3/MPEGGenre.hpp
	@echo [#] Compiling file ./Source/Sound/MP3/MPEGGenre.hpp
	g++ -c ./Source/Sound/MP3/MPEGGenre.hpp
#-------------------------------------------------------------------------------------------------
bin/MPEGAudioTag.cpp.o: ./Source/Sound/MP3/MPEGAudioTag.cpp
	@echo [#] Compiling file ./Source/Sound/MP3/MPEGAudioTag.cpp
	g++ -c ./Source/Sound/MP3/MPEGAudioTag.cpp
#-------------------------------------------------------------------------------------------------
bin/SoundPlayStyle.hpp.o: ./Source/Sound/SoundPlayStyle.hpp
	@echo [#] Compiling file ./Source/Sound/SoundPlayStyle.hpp
	g++ -c ./Source/Sound/SoundPlayStyle.hpp
#-------------------------------------------------------------------------------------------------
bin/FMT.cpp.o: ./Source/Sound/WAV/FMT.cpp
	@echo [#] Compiling file ./Source/Sound/WAV/FMT.cpp
	g++ -c ./Source/Sound/WAV/FMT.cpp
#-------------------------------------------------------------------------------------------------
bin/RIFF.cpp.o: ./Source/Sound/WAV/RIFF.cpp
	@echo [#] Compiling file ./Source/Sound/WAV/RIFF.cpp
	g++ -c ./Source/Sound/WAV/RIFF.cpp
#-------------------------------------------------------------------------------------------------
bin/WAV.cpp.o: ./Source/Sound/WAV/WAV.cpp
	@echo [#] Compiling file ./Source/Sound/WAV/WAV.cpp
	g++ -c ./Source/Sound/WAV/WAV.cpp
#-------------------------------------------------------------------------------------------------
bin/M4A.cpp.o: ./Source/Sound/M4A/M4A.cpp
	@echo [#] Compiling file ./Source/Sound/M4A/M4A.cpp
	g++ -c ./Source/Sound/M4A/M4A.cpp
#-------------------------------------------------------------------------------------------------
bin/Sound.cpp.o: ./Source/Sound/Sound.cpp
	@echo [#] Compiling file ./Source/Sound/Sound.cpp
	g++ -c ./Source/Sound/Sound.cpp
#-------------------------------------------------------------------------------------------------
bin/WMA.cpp.o: ./Source/Sound/WMA/WMA.cpp
	@echo [#] Compiling file ./Source/Sound/WMA/WMA.cpp
	g++ -c ./Source/Sound/WMA/WMA.cpp
#-------------------------------------------------------------------------------------------------
bin/OGG.cpp.o: ./Source/Sound/OGG/OGG.cpp
	@echo [#] Compiling file ./Source/Sound/OGG/OGG.cpp
	g++ -c ./Source/Sound/OGG/OGG.cpp
#-------------------------------------------------------------------------------------------------
bin/FLAC.cpp.o: ./Source/Sound/FLAC/FLAC.cpp
	@echo [#] Compiling file ./Source/Sound/FLAC/FLAC.cpp
	g++ -c ./Source/Sound/FLAC/FLAC.cpp
#-------------------------------------------------------------------------------------------------
bin/MIDITrackHeader.cpp.o: ./Source/Sound/MID/MIDITrackHeader.cpp
	@echo [#] Compiling file ./Source/Sound/MID/MIDITrackHeader.cpp
	g++ -c ./Source/Sound/MID/MIDITrackHeader.cpp
#-------------------------------------------------------------------------------------------------
bin/MIDICommandExtended.cpp.o: ./Source/Sound/MID/MIDICommandExtended.cpp
	@echo [#] Compiling file ./Source/Sound/MID/MIDICommandExtended.cpp
	g++ -c ./Source/Sound/MID/MIDICommandExtended.cpp
#-------------------------------------------------------------------------------------------------
bin/MID.cpp.o: ./Source/Sound/MID/MID.cpp
	@echo [#] Compiling file ./Source/Sound/MID/MID.cpp
	g++ -c ./Source/Sound/MID/MID.cpp
#-------------------------------------------------------------------------------------------------
bin/MIDINote.cpp.o: ./Source/Sound/MID/MIDINote.cpp
	@echo [#] Compiling file ./Source/Sound/MID/MIDINote.cpp
	g++ -c ./Source/Sound/MID/MIDINote.cpp
#-------------------------------------------------------------------------------------------------
bin/MIDICommand.cpp.o: ./Source/Sound/MID/MIDICommand.cpp
	@echo [#] Compiling file ./Source/Sound/MID/MIDICommand.cpp
	g++ -c ./Source/Sound/MID/MIDICommand.cpp
#-------------------------------------------------------------------------------------------------
bin/MIDITrack.cpp.o: ./Source/Sound/MID/MIDITrack.cpp
	@echo [#] Compiling file ./Source/Sound/MID/MIDITrack.cpp
	g++ -c ./Source/Sound/MID/MIDITrack.cpp
#-------------------------------------------------------------------------------------------------
bin/AAC.cpp.o: ./Source/Sound/AAC/AAC.cpp
	@echo [#] Compiling file ./Source/Sound/AAC/AAC.cpp
	g++ -c ./Source/Sound/AAC/AAC.cpp
#-------------------------------------------------------------------------------------------------
bin/ISoundFormat.hpp.o: ./Source/Sound/ISoundFormat.hpp
	@echo [#] Compiling file ./Source/Sound/ISoundFormat.hpp
	g++ -c ./Source/Sound/ISoundFormat.hpp
#-------------------------------------------------------------------------------------------------
bin/ICypher.cpp.o: ./Source/Encryption/ICypher.cpp
	@echo [#] Compiling file ./Source/Encryption/ICypher.cpp
	g++ -c ./Source/Encryption/ICypher.cpp
#-------------------------------------------------------------------------------------------------
bin/RSA.cpp.o: ./Source/Encryption/RSA.cpp
	@echo [#] Compiling file ./Source/Encryption/RSA.cpp
	g++ -c ./Source/Encryption/RSA.cpp
#-------------------------------------------------------------------------------------------------
bin/Caesar.cpp.o: ./Source/Encryption/Caesar.cpp
	@echo [#] Compiling file ./Source/Encryption/Caesar.cpp
	g++ -c ./Source/Encryption/Caesar.cpp
#-------------------------------------------------------------------------------------------------
bin/ResourceType.hpp.o: ./Source/ResourceType.hpp
	@echo [#] Compiling file ./Source/ResourceType.hpp
	g++ -c ./Source/ResourceType.hpp
#-------------------------------------------------------------------------------------------------
bin/Video.cpp.o: ./Source/Video/Video.cpp
	@echo [#] Compiling file ./Source/Video/Video.cpp
	g++ -c ./Source/Video/Video.cpp
#-------------------------------------------------------------------------------------------------
bin/MP4.cpp.o: ./Source/Video/MP4/MP4.cpp
	@echo [#] Compiling file ./Source/Video/MP4/MP4.cpp
	g++ -c ./Source/Video/MP4/MP4.cpp
#-------------------------------------------------------------------------------------------------
bin/IVideoFormat.hpp.o: ./Source/Video/IVideoFormat.hpp
	@echo [#] Compiling file ./Source/Video/IVideoFormat.hpp
	g++ -c ./Source/Video/IVideoFormat.hpp
#-------------------------------------------------------------------------------------------------
bin/AVI.cpp.o: ./Source/Video/AVI/AVI.cpp
	@echo [#] Compiling file ./Source/Video/AVI/AVI.cpp
	g++ -c ./Source/Video/AVI/AVI.cpp
#-------------------------------------------------------------------------------------------------
bin/AVIHeader.cpp.o: ./Source/Video/AVI/AVIHeader.cpp
	@echo [#] Compiling file ./Source/Video/AVI/AVIHeader.cpp
	g++ -c ./Source/Video/AVI/AVIHeader.cpp
#-------------------------------------------------------------------------------------------------
bin/Dialog.cpp.o: ./Source/Dialog/Dialog.cpp
	@echo [#] Compiling file ./Source/Dialog/Dialog.cpp
	g++ -c ./Source/Dialog/Dialog.cpp
#-------------------------------------------------------------------------------------------------
bin/FNTCharacter.cpp.o: ./Source/Font/FNT/FNTCharacter.cpp
	@echo [#] Compiling file ./Source/Font/FNT/FNTCharacter.cpp
	g++ -c ./Source/Font/FNT/FNTCharacter.cpp
#-------------------------------------------------------------------------------------------------
bin/FNTInfo.cpp.o: ./Source/Font/FNT/FNTInfo.cpp
	@echo [#] Compiling file ./Source/Font/FNT/FNTInfo.cpp
	g++ -c ./Source/Font/FNT/FNTInfo.cpp
#-------------------------------------------------------------------------------------------------
bin/FNTPage.cpp.o: ./Source/Font/FNT/FNTPage.cpp
	@echo [#] Compiling file ./Source/Font/FNT/FNTPage.cpp
	g++ -c ./Source/Font/FNT/FNTPage.cpp
#-------------------------------------------------------------------------------------------------
bin/FNT.cpp.o: ./Source/Font/FNT/FNT.cpp
	@echo [#] Compiling file ./Source/Font/FNT/FNT.cpp
	g++ -c ./Source/Font/FNT/FNT.cpp
#-------------------------------------------------------------------------------------------------
bin/FNTCommonData.cpp.o: ./Source/Font/FNT/FNTCommonData.cpp
	@echo [#] Compiling file ./Source/Font/FNT/FNTCommonData.cpp
	g++ -c ./Source/Font/FNT/FNTCommonData.cpp
#-------------------------------------------------------------------------------------------------
bin/IFontFormat.hpp.o: ./Source/Font/IFontFormat.hpp
	@echo [#] Compiling file ./Source/Font/IFontFormat.hpp
	g++ -c ./Source/Font/IFontFormat.hpp
#-------------------------------------------------------------------------------------------------
bin/OTF.cpp.o: ./Source/Font/OTF/OTF.cpp
	@echo [#] Compiling file ./Source/Font/OTF/OTF.cpp
	g++ -c ./Source/Font/OTF/OTF.cpp
#-------------------------------------------------------------------------------------------------
bin/Font.cpp.o: ./Source/Font/Font.cpp
	@echo [#] Compiling file ./Source/Font/Font.cpp
	g++ -c ./Source/Font/Font.cpp
#-------------------------------------------------------------------------------------------------
bin/TTF.cpp.o: ./Source/Font/TTF/TTF.cpp
	@echo [#] Compiling file ./Source/Font/TTF/TTF.cpp
	g++ -c ./Source/Font/TTF/TTF.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFTableEntry.cpp.o: ./Source/Font/TTF/TTFTableEntry.cpp
	@echo [#] Compiling file ./Source/Font/TTF/TTFTableEntry.cpp
	g++ -c ./Source/Font/TTF/TTFTableEntry.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFVersion.cpp.o: ./Source/Font/TTF/Chunks/TTFVersion.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/TTFVersion.cpp
	g++ -c ./Source/Font/TTF/Chunks/TTFVersion.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFHeader.cpp.o: ./Source/Font/TTF/Chunks/TTFHeader.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/TTFHeader.cpp
	g++ -c ./Source/Font/TTF/Chunks/TTFHeader.cpp
#-------------------------------------------------------------------------------------------------
bin/EncodingID.cpp.o: ./Source/Font/TTF/Chunks/CMAP/EncodingID.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/CMAP/EncodingID.cpp
	g++ -c ./Source/Font/TTF/Chunks/CMAP/EncodingID.cpp
#-------------------------------------------------------------------------------------------------
bin/PlatformID.cpp.o: ./Source/Font/TTF/Chunks/CMAP/PlatformID.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/CMAP/PlatformID.cpp
	g++ -c ./Source/Font/TTF/Chunks/CMAP/PlatformID.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFCharacterMapping.cpp.o: ./Source/Font/TTF/Chunks/CMAP/TTFCharacterMapping.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/CMAP/TTFCharacterMapping.cpp
	g++ -c ./Source/Font/TTF/Chunks/CMAP/TTFCharacterMapping.cpp
#-------------------------------------------------------------------------------------------------
bin/EncodingRecord.cpp.o: ./Source/Font/TTF/Chunks/CMAP/EncodingRecord.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/CMAP/EncodingRecord.cpp
	g++ -c ./Source/Font/TTF/Chunks/CMAP/EncodingRecord.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFOffsetTable.cpp.o: ./Source/Font/TTF/Chunks/TTFOffsetTable.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/TTFOffsetTable.cpp
	g++ -c ./Source/Font/TTF/Chunks/TTFOffsetTable.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFVersionType.cpp.o: ./Source/Font/TTF/Chunks/TTFVersionType.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/TTFVersionType.cpp
	g++ -c ./Source/Font/TTF/Chunks/TTFVersionType.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFCompatibility.cpp.o: ./Source/Font/TTF/Chunks/OS2/TTFCompatibility.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/OS2/TTFCompatibility.cpp
	g++ -c ./Source/Font/TTF/Chunks/OS2/TTFCompatibility.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFLetterform.cpp.o: ./Source/Font/TTF/Chunks/OS2/Panose/TTFLetterform.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/OS2/Panose/TTFLetterform.cpp
	g++ -c ./Source/Font/TTF/Chunks/OS2/Panose/TTFLetterform.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFContrast.cpp.o: ./Source/Font/TTF/Chunks/OS2/Panose/TTFContrast.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/OS2/Panose/TTFContrast.cpp
	g++ -c ./Source/Font/TTF/Chunks/OS2/Panose/TTFContrast.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFMidline.cpp.o: ./Source/Font/TTF/Chunks/OS2/Panose/TTFMidline.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/OS2/Panose/TTFMidline.cpp
	g++ -c ./Source/Font/TTF/Chunks/OS2/Panose/TTFMidline.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFPanose.cpp.o: ./Source/Font/TTF/Chunks/OS2/Panose/TTFPanose.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/OS2/Panose/TTFPanose.cpp
	g++ -c ./Source/Font/TTF/Chunks/OS2/Panose/TTFPanose.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFArmStyle.cpp.o: ./Source/Font/TTF/Chunks/OS2/Panose/TTFArmStyle.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/OS2/Panose/TTFArmStyle.cpp
	g++ -c ./Source/Font/TTF/Chunks/OS2/Panose/TTFArmStyle.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFProportion.cpp.o: ./Source/Font/TTF/Chunks/OS2/Panose/TTFProportion.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/OS2/Panose/TTFProportion.cpp
	g++ -c ./Source/Font/TTF/Chunks/OS2/Panose/TTFProportion.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFWeight.cpp.o: ./Source/Font/TTF/Chunks/OS2/Panose/TTFWeight.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/OS2/Panose/TTFWeight.cpp
	g++ -c ./Source/Font/TTF/Chunks/OS2/Panose/TTFWeight.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFHeightX.cpp.o: ./Source/Font/TTF/Chunks/OS2/Panose/TTFHeightX.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/OS2/Panose/TTFHeightX.cpp
	g++ -c ./Source/Font/TTF/Chunks/OS2/Panose/TTFHeightX.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFSerifStyle.cpp.o: ./Source/Font/TTF/Chunks/OS2/Panose/TTFSerifStyle.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/OS2/Panose/TTFSerifStyle.cpp
	g++ -c ./Source/Font/TTF/Chunks/OS2/Panose/TTFSerifStyle.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFStrokeVariatoon.cpp.o: ./Source/Font/TTF/Chunks/OS2/Panose/TTFStrokeVariatoon.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/OS2/Panose/TTFStrokeVariatoon.cpp
	g++ -c ./Source/Font/TTF/Chunks/OS2/Panose/TTFStrokeVariatoon.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFFamilyType.cpp.o: ./Source/Font/TTF/Chunks/OS2/Panose/TTFFamilyType.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/OS2/Panose/TTFFamilyType.cpp
	g++ -c ./Source/Font/TTF/Chunks/OS2/Panose/TTFFamilyType.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFHorizontalHeader.cpp.o: ./Source/Font/TTF/Chunks/TTFHorizontalHeader.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/TTFHorizontalHeader.cpp
	g++ -c ./Source/Font/TTF/Chunks/TTFHorizontalHeader.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFKerning.cpp.o: ./Source/Font/TTF/Chunks/KERN/TTFKerning.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/KERN/TTFKerning.cpp
	g++ -c ./Source/Font/TTF/Chunks/KERN/TTFKerning.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFSubtableFormat0.cpp.o: ./Source/Font/TTF/Chunks/KERN/TTFSubtableFormat0.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/KERN/TTFSubtableFormat0.cpp
	g++ -c ./Source/Font/TTF/Chunks/KERN/TTFSubtableFormat0.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFKerningSubtable.cpp.o: ./Source/Font/TTF/Chunks/KERN/TTFKerningSubtable.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/KERN/TTFKerningSubtable.cpp
	g++ -c ./Source/Font/TTF/Chunks/KERN/TTFKerningSubtable.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFSubtableFormat2.cpp.o: ./Source/Font/TTF/Chunks/KERN/TTFSubtableFormat2.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/KERN/TTFSubtableFormat2.cpp
	g++ -c ./Source/Font/TTF/Chunks/KERN/TTFSubtableFormat2.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFKerningPair.cpp.o: ./Source/Font/TTF/Chunks/KERN/TTFKerningPair.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/KERN/TTFKerningPair.cpp
	g++ -c ./Source/Font/TTF/Chunks/KERN/TTFKerningPair.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFPostScript.cpp.o: ./Source/Font/TTF/Chunks/TTFPostScript.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/TTFPostScript.cpp
	g++ -c ./Source/Font/TTF/Chunks/TTFPostScript.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFMaximumProfile.cpp.o: ./Source/Font/TTF/Chunks/TTFMaximumProfile.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/TTFMaximumProfile.cpp
	g++ -c ./Source/Font/TTF/Chunks/TTFMaximumProfile.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFLinearThreshold.cpp.o: ./Source/Font/TTF/Chunks/TTFLinearThreshold.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/TTFLinearThreshold.cpp
	g++ -c ./Source/Font/TTF/Chunks/TTFLinearThreshold.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFDigitalSignatureBlock.cpp.o: ./Source/Font/TTF/Chunks/DSIG/TTFDigitalSignatureBlock.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/DSIG/TTFDigitalSignatureBlock.cpp
	g++ -c ./Source/Font/TTF/Chunks/DSIG/TTFDigitalSignatureBlock.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFDigitalSignatureRecord.cpp.o: ./Source/Font/TTF/Chunks/DSIG/TTFDigitalSignatureRecord.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/DSIG/TTFDigitalSignatureRecord.cpp
	g++ -c ./Source/Font/TTF/Chunks/DSIG/TTFDigitalSignatureRecord.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFDigitalSignature.cpp.o: ./Source/Font/TTF/Chunks/DSIG/TTFDigitalSignature.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/DSIG/TTFDigitalSignature.cpp
	g++ -c ./Source/Font/TTF/Chunks/DSIG/TTFDigitalSignature.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFVerticalDeviceMetrics.cpp.o: ./Source/Font/TTF/Chunks/TTFVerticalDeviceMetrics.cpp
	@echo [#] Compiling file ./Source/Font/TTF/Chunks/TTFVerticalDeviceMetrics.cpp
	g++ -c ./Source/Font/TTF/Chunks/TTFVerticalDeviceMetrics.cpp
#-------------------------------------------------------------------------------------------------
bin/TTFTableEntryType.cpp.o: ./Source/Font/TTF/TTFTableEntryType.cpp
	@echo [#] Compiling file ./Source/Font/TTF/TTFTableEntryType.cpp
	g++ -c ./Source/Font/TTF/TTFTableEntryType.cpp
#-------------------------------------------------------------------------------------------------
bin/Event.hpp.o: ./Source/Event/Event.hpp
	@echo [#] Compiling file ./Source/Event/Event.hpp
	g++ -c ./Source/Event/Event.hpp
#-------------------------------------------------------------------------------------------------
bin/FBX.cpp.o: ./Source/Model/FBX/FBX.cpp
	@echo [#] Compiling file ./Source/Model/FBX/FBX.cpp
	g++ -c ./Source/Model/FBX/FBX.cpp
#-------------------------------------------------------------------------------------------------
bin/Material.cpp.o: ./Source/Model/Material.cpp
	@echo [#] Compiling file ./Source/Model/Material.cpp
	g++ -c ./Source/Model/Material.cpp
#-------------------------------------------------------------------------------------------------
bin/Model.cpp.o: ./Source/Model/Model.cpp
	@echo [#] Compiling file ./Source/Model/Model.cpp
	g++ -c ./Source/Model/Model.cpp
#-------------------------------------------------------------------------------------------------
bin/MeshStructure.cpp.o: ./Source/Model/MeshStructure.cpp
	@echo [#] Compiling file ./Source/Model/MeshStructure.cpp
	g++ -c ./Source/Model/MeshStructure.cpp
#-------------------------------------------------------------------------------------------------
bin/A3DS.cpp.o: ./Source/Model/3DS/A3DS.cpp
	@echo [#] Compiling file ./Source/Model/3DS/A3DS.cpp
	g++ -c ./Source/Model/3DS/A3DS.cpp
#-------------------------------------------------------------------------------------------------
bin/Mesh.cpp.o: ./Source/Model/Mesh.cpp
	@echo [#] Compiling file ./Source/Model/Mesh.cpp
	g++ -c ./Source/Model/Mesh.cpp
#-------------------------------------------------------------------------------------------------
bin/IModelFormat.hpp.o: ./Source/Model/IModelFormat.hpp
	@echo [#] Compiling file ./Source/Model/IModelFormat.hpp
	g++ -c ./Source/Model/IModelFormat.hpp
#-------------------------------------------------------------------------------------------------
bin/MeshRenderInfo.cpp.o: ./Source/Model/MeshRenderInfo.cpp
	@echo [#] Compiling file ./Source/Model/MeshRenderInfo.cpp
	g++ -c ./Source/Model/MeshRenderInfo.cpp
#-------------------------------------------------------------------------------------------------
bin/Vertex.cpp.o: ./Source/Model/Vertex.cpp
	@echo [#] Compiling file ./Source/Model/Vertex.cpp
	g++ -c ./Source/Model/Vertex.cpp
#-------------------------------------------------------------------------------------------------
bin/WRL.cpp.o: ./Source/Model/WRL/WRL.cpp
	@echo [#] Compiling file ./Source/Model/WRL/WRL.cpp
	g++ -c ./Source/Model/WRL/WRL.cpp
#-------------------------------------------------------------------------------------------------
bin/LinkedMesh.cpp.o: ./Source/Model/LinkedMesh.cpp
	@echo [#] Compiling file ./Source/Model/LinkedMesh.cpp
	g++ -c ./Source/Model/LinkedMesh.cpp
#-------------------------------------------------------------------------------------------------
bin/STL.cpp.o: ./Source/Model/STL/STL.cpp
	@echo [#] Compiling file ./Source/Model/STL/STL.cpp
	g++ -c ./Source/Model/STL/STL.cpp
#-------------------------------------------------------------------------------------------------
bin/PLY.cpp.o: ./Source/Model/PLY/PLY.cpp
	@echo [#] Compiling file ./Source/Model/PLY/PLY.cpp
	g++ -c ./Source/Model/PLY/PLY.cpp
#-------------------------------------------------------------------------------------------------
bin/OBJ.cpp.o: ./Source/Model/OBJ/OBJ.cpp
	@echo [#] Compiling file ./Source/Model/OBJ/OBJ.cpp
	g++ -c ./Source/Model/OBJ/OBJ.cpp
#-------------------------------------------------------------------------------------------------
bin/MTL.cpp.o: ./Source/Model/OBJ/MTL/MTL.cpp
	@echo [#] Compiling file ./Source/Model/OBJ/MTL/MTL.cpp
	g++ -c ./Source/Model/OBJ/MTL/MTL.cpp
#-------------------------------------------------------------------------------------------------
bin/OBJElement.cpp.o: ./Source/Model/OBJ/OBJElement.cpp
	@echo [#] Compiling file ./Source/Model/OBJ/OBJElement.cpp
	g++ -c ./Source/Model/OBJ/OBJElement.cpp
#-------------------------------------------------------------------------------------------------
bin/MeshIndexData.cpp.o: ./Source/Model/MeshIndexData.cpp
	@echo [#] Compiling file ./Source/Model/MeshIndexData.cpp
	g++ -c ./Source/Model/MeshIndexData.cpp
#-------------------------------------------------------------------------------------------------
bin/HTTPServer.cpp.o: ./Source/Service/HTTP/HTTPServer.cpp
	@echo [#] Compiling file ./Source/Service/HTTP/HTTPServer.cpp
	g++ -c ./Source/Service/HTTP/HTTPServer.cpp
#-------------------------------------------------------------------------------------------------
bin/HTTPError.cpp.o: ./Source/Service/HTTP/HTTPError.cpp
	@echo [#] Compiling file ./Source/Service/HTTP/HTTPError.cpp
	g++ -c ./Source/Service/HTTP/HTTPError.cpp
#-------------------------------------------------------------------------------------------------
bin/HTTPRequestMethod.cpp.o: ./Source/Service/HTTP/HTTPRequestMethod.cpp
	@echo [#] Compiling file ./Source/Service/HTTP/HTTPRequestMethod.cpp
	g++ -c ./Source/Service/HTTP/HTTPRequestMethod.cpp
#-------------------------------------------------------------------------------------------------
bin/ADAM7.cpp.o: ./Source/Compression/ADAM7/ADAM7.cpp
	@echo [#] Compiling file ./Source/Compression/ADAM7/ADAM7.cpp
	g++ -c ./Source/Compression/ADAM7/ADAM7.cpp
#-------------------------------------------------------------------------------------------------
bin/ZLIB.cpp.o: ./Source/Compression/ZLIB/ZLIB.cpp
	@echo [#] Compiling file ./Source/Compression/ZLIB/ZLIB.cpp
	g++ -c ./Source/Compression/ZLIB/ZLIB.cpp
#-------------------------------------------------------------------------------------------------
bin/ZLIBHeader.cpp.o: ./Source/Compression/ZLIB/ZLIBHeader.cpp
	@echo [#] Compiling file ./Source/Compression/ZLIB/ZLIBHeader.cpp
	g++ -c ./Source/Compression/ZLIB/ZLIBHeader.cpp
#-------------------------------------------------------------------------------------------------
bin/ZLIBCompressionMethod.cpp.o: ./Source/Compression/ZLIB/ZLIBCompressionMethod.cpp
	@echo [#] Compiling file ./Source/Compression/ZLIB/ZLIBCompressionMethod.cpp
	g++ -c ./Source/Compression/ZLIB/ZLIBCompressionMethod.cpp
#-------------------------------------------------------------------------------------------------
bin/ZLIBCompressionLevel.cpp.o: ./Source/Compression/ZLIB/ZLIBCompressionLevel.cpp
	@echo [#] Compiling file ./Source/Compression/ZLIB/ZLIBCompressionLevel.cpp
	g++ -c ./Source/Compression/ZLIB/ZLIBCompressionLevel.cpp
#-------------------------------------------------------------------------------------------------
bin/HuffmanCodeType.cpp.o: ./Source/Compression/HUFFMAN/HuffmanCodeType.cpp
	@echo [#] Compiling file ./Source/Compression/HUFFMAN/HuffmanCodeType.cpp
	g++ -c ./Source/Compression/HUFFMAN/HuffmanCodeType.cpp
#-------------------------------------------------------------------------------------------------
bin/HuffmanTree.cpp.o: ./Source/Compression/HUFFMAN/HuffmanTree.cpp
	@echo [#] Compiling file ./Source/Compression/HUFFMAN/HuffmanTree.cpp
	g++ -c ./Source/Compression/HUFFMAN/HuffmanTree.cpp
#-------------------------------------------------------------------------------------------------
bin/HuffmanSymbol.cpp.o: ./Source/Compression/HUFFMAN/HuffmanSymbol.cpp
	@echo [#] Compiling file ./Source/Compression/HUFFMAN/HuffmanSymbol.cpp
	g++ -c ./Source/Compression/HUFFMAN/HuffmanSymbol.cpp
#-------------------------------------------------------------------------------------------------
bin/HuffmanNumberCode.cpp.o: ./Source/Compression/HUFFMAN/HuffmanNumberCode.cpp
	@echo [#] Compiling file ./Source/Compression/HUFFMAN/HuffmanNumberCode.cpp
	g++ -c ./Source/Compression/HUFFMAN/HuffmanNumberCode.cpp
#-------------------------------------------------------------------------------------------------
bin/DeflateBlock.cpp.o: ./Source/Compression/DEFLATE/DeflateBlock.cpp
	@echo [#] Compiling file ./Source/Compression/DEFLATE/DeflateBlock.cpp
	g++ -c ./Source/Compression/DEFLATE/DeflateBlock.cpp
#-------------------------------------------------------------------------------------------------
bin/DeflateEncodingMethod.cpp.o: ./Source/Compression/DEFLATE/DeflateEncodingMethod.cpp
	@echo [#] Compiling file ./Source/Compression/DEFLATE/DeflateEncodingMethod.cpp
	g++ -c ./Source/Compression/DEFLATE/DeflateEncodingMethod.cpp
#-------------------------------------------------------------------------------------------------
bin/Bash.cpp.o: ./Source/File/Bash.cpp
	@echo [#] Compiling file ./Source/File/Bash.cpp
	g++ -c ./Source/File/Bash.cpp
#-------------------------------------------------------------------------------------------------
bin/FileStream.cpp.o: ./Source/File/FileStream.cpp
	@echo [#] Compiling file ./Source/File/FileStream.cpp
	g++ -c ./Source/File/FileStream.cpp
#-------------------------------------------------------------------------------------------------
bin/ProgramExecuteResultListener.hpp.o: ./Source/File/ProgramExecuteResultListener.hpp
	@echo [#] Compiling file ./Source/File/ProgramExecuteResultListener.hpp
	g++ -c ./Source/File/ProgramExecuteResultListener.hpp
#-------------------------------------------------------------------------------------------------
bin/FileOpenMode.hpp.o: ./Source/File/FileOpenMode.hpp
	@echo [#] Compiling file ./Source/File/FileOpenMode.hpp
	g++ -c ./Source/File/FileOpenMode.hpp
#-------------------------------------------------------------------------------------------------
bin/ProgramExecuteInfo.cpp.o: ./Source/File/ProgramExecuteInfo.cpp
	@echo [#] Compiling file ./Source/File/ProgramExecuteInfo.cpp
	g++ -c ./Source/File/ProgramExecuteInfo.cpp
#-------------------------------------------------------------------------------------------------
bin/ByteStream.cpp.o: ./Source/File/ByteStream.cpp
	@echo [#] Compiling file ./Source/File/ByteStream.cpp
	g++ -c ./Source/File/ByteStream.cpp
#-------------------------------------------------------------------------------------------------
bin/FilePersistence.hpp.o: ./Source/File/FilePersistence.hpp
	@echo [#] Compiling file ./Source/File/FilePersistence.hpp
	g++ -c ./Source/File/FilePersistence.hpp
#-------------------------------------------------------------------------------------------------
bin/IFIle.cpp.o: ./Source/File/IFIle.cpp
	@echo [#] Compiling file ./Source/File/IFIle.cpp
	g++ -c ./Source/File/IFIle.cpp
#-------------------------------------------------------------------------------------------------
bin/FileTemporary.cpp.o: ./Source/File/FileTemporary.cpp
	@echo [#] Compiling file ./Source/File/FileTemporary.cpp
	g++ -c ./Source/File/FileTemporary.cpp
#-------------------------------------------------------------------------------------------------
bin/FileActionResult.hpp.o: ./Source/File/FileActionResult.hpp
	@echo [#] Compiling file ./Source/File/FileActionResult.hpp
	g++ -c ./Source/File/FileActionResult.hpp
#-------------------------------------------------------------------------------------------------
bin/OpenFileDialog.cpp.o: ./Source/File/OpenFileDialog.cpp
	@echo [#] Compiling file ./Source/File/OpenFileDialog.cpp
	g++ -c ./Source/File/OpenFileDialog.cpp
#-------------------------------------------------------------------------------------------------
bin/Program.cpp.o: ./Source/File/Program.cpp
	@echo [#] Compiling file ./Source/File/Program.cpp
	g++ -c ./Source/File/Program.cpp
#-------------------------------------------------------------------------------------------------
bin/File.cpp.o: ./Source/File/File.cpp
	@echo [#] Compiling file ./Source/File/File.cpp
	g++ -c ./Source/File/File.cpp
#-------------------------------------------------------------------------------------------------
bin/Level.cpp.o: ./Source/Level/Level.cpp
	@echo [#] Compiling file ./Source/Level/Level.cpp
	g++ -c ./Source/Level/Level.cpp
#-------------------------------------------------------------------------------------------------
bin/SkyBox.cpp.o: ./Source/Game/SkyBox.cpp
	@echo [#] Compiling file ./Source/Game/SkyBox.cpp
	g++ -c ./Source/Game/SkyBox.cpp
#-------------------------------------------------------------------------------------------------
bin/Sprite.cpp.o: ./Source/Game/Sprite.cpp
	@echo [#] Compiling file ./Source/Game/Sprite.cpp
	g++ -c ./Source/Game/Sprite.cpp
#-------------------------------------------------------------------------------------------------
bin/EML.cpp.o: ./Source/Email/EML.cpp
	@echo [#] Compiling file ./Source/Email/EML.cpp
	g++ -c ./Source/Email/EML.cpp
#-------------------------------------------------------------------------------------------------
bin/ShaderType.cpp.o: ./Source/Shader/ShaderType.cpp
	@echo [#] Compiling file ./Source/Shader/ShaderType.cpp
	g++ -c ./Source/Shader/ShaderType.cpp
#-------------------------------------------------------------------------------------------------
bin/Shader.cpp.o: ./Source/Shader/Shader.cpp
	@echo [#] Compiling file ./Source/Shader/Shader.cpp
	g++ -c ./Source/Shader/Shader.cpp
#-------------------------------------------------------------------------------------------------
bin/ShaderProgram.cpp.o: ./Source/Shader/ShaderProgram.cpp
	@echo [#] Compiling file ./Source/Shader/ShaderProgram.cpp
	g++ -c ./Source/Shader/ShaderProgram.cpp
#-------------------------------------------------------------------------------------------------
bin/Queue.hpp.o: ./Source/Container/Queue.hpp
	@echo [#] Compiling file ./Source/Container/Queue.hpp
	g++ -c ./Source/Container/Queue.hpp
#-------------------------------------------------------------------------------------------------
bin/DictionaryStatic.hpp.o: ./Source/Container/DictionaryStatic.hpp
	@echo [#] Compiling file ./Source/Container/DictionaryStatic.hpp
	g++ -c ./Source/Container/DictionaryStatic.hpp
#-------------------------------------------------------------------------------------------------
bin/BitStreamHusk.cpp.o: ./Source/Container/BitStreamHusk.cpp
	@echo [#] Compiling file ./Source/Container/BitStreamHusk.cpp
	g++ -c ./Source/Container/BitStreamHusk.cpp
#-------------------------------------------------------------------------------------------------
bin/Table.hpp.o: ./Source/Container/Table.hpp
	@echo [#] Compiling file ./Source/Container/Table.hpp
	g++ -c ./Source/Container/Table.hpp
#-------------------------------------------------------------------------------------------------
bin/AsciiString.cpp.o: ./Source/Container/AsciiString.cpp
	@echo [#] Compiling file ./Source/Container/AsciiString.cpp
	g++ -c ./Source/Container/AsciiString.cpp
#-------------------------------------------------------------------------------------------------
bin/LinkedListNode.hpp.o: ./Source/Container/LinkedListNode.hpp
	@echo [#] Compiling file ./Source/Container/LinkedListNode.hpp
	g++ -c ./Source/Container/LinkedListNode.hpp
#-------------------------------------------------------------------------------------------------
bin/RingBuffer.hpp.o: ./Source/Container/RingBuffer.hpp
	@echo [#] Compiling file ./Source/Container/RingBuffer.hpp
	g++ -c ./Source/Container/RingBuffer.hpp
#-------------------------------------------------------------------------------------------------
bin/Dictionary.hpp.o: ./Source/Container/Dictionary.hpp
	@echo [#] Compiling file ./Source/Container/Dictionary.hpp
	g++ -c ./Source/Container/Dictionary.hpp
#-------------------------------------------------------------------------------------------------
bin/BinaryTreeNode.hpp.o: ./Source/Container/BinaryTree/BinaryTreeNode.hpp
	@echo [#] Compiling file ./Source/Container/BinaryTree/BinaryTreeNode.hpp
	g++ -c ./Source/Container/BinaryTree/BinaryTreeNode.hpp
#-------------------------------------------------------------------------------------------------
bin/BinaryTree.hpp.o: ./Source/Container/BinaryTree/BinaryTree.hpp
	@echo [#] Compiling file ./Source/Container/BinaryTree/BinaryTree.hpp
	g++ -c ./Source/Container/BinaryTree/BinaryTree.hpp
#-------------------------------------------------------------------------------------------------
bin/BinaryTreeData.hpp.o: ./Source/Container/BinaryTree/BinaryTreeData.hpp
	@echo [#] Compiling file ./Source/Container/BinaryTree/BinaryTreeData.hpp
	g++ -c ./Source/Container/BinaryTree/BinaryTreeData.hpp
#-------------------------------------------------------------------------------------------------
bin/List.hpp.o: ./Source/Container/List.hpp
	@echo [#] Compiling file ./Source/Container/List.hpp
	g++ -c ./Source/Container/List.hpp
#-------------------------------------------------------------------------------------------------
bin/QuadTreeDirection.hpp.o: ./Source/Container/QuadTree/QuadTreeDirection.hpp
	@echo [#] Compiling file ./Source/Container/QuadTree/QuadTreeDirection.hpp
	g++ -c ./Source/Container/QuadTree/QuadTreeDirection.hpp
#-------------------------------------------------------------------------------------------------
bin/QuadTreePosition.hpp.o: ./Source/Container/QuadTree/QuadTreePosition.hpp
	@echo [#] Compiling file ./Source/Container/QuadTree/QuadTreePosition.hpp
	g++ -c ./Source/Container/QuadTree/QuadTreePosition.hpp
#-------------------------------------------------------------------------------------------------
bin/QuadTree.hpp.o: ./Source/Container/QuadTree/QuadTree.hpp
	@echo [#] Compiling file ./Source/Container/QuadTree/QuadTree.hpp
	g++ -c ./Source/Container/QuadTree/QuadTree.hpp
#-------------------------------------------------------------------------------------------------
bin/QuadTreeNode.hpp.o: ./Source/Container/QuadTree/QuadTreeNode.hpp
	@echo [#] Compiling file ./Source/Container/QuadTree/QuadTreeNode.hpp
	g++ -c ./Source/Container/QuadTree/QuadTreeNode.hpp
#-------------------------------------------------------------------------------------------------
bin/LinkedList.hpp.o: ./Source/Container/LinkedList.hpp
	@echo [#] Compiling file ./Source/Container/LinkedList.hpp
	g++ -c ./Source/Container/LinkedList.hpp
#-------------------------------------------------------------------------------------------------
bin/IFileFormat.hpp.o: ./Source/IFileFormat.hpp
	@echo [#] Compiling file ./Source/IFileFormat.hpp
	g++ -c ./Source/IFileFormat.hpp
#-------------------------------------------------------------------------------------------------
bin/Camera.cpp.o: ./Source/Camera/Camera.cpp
	@echo [#] Compiling file ./Source/Camera/Camera.cpp
	g++ -c ./Source/Camera/Camera.cpp
#-------------------------------------------------------------------------------------------------
bin/CameraPerspective.hpp.o: ./Source/Camera/CameraPerspective.hpp
	@echo [#] Compiling file ./Source/Camera/CameraPerspective.hpp
	g++ -c ./Source/Camera/CameraPerspective.hpp
#-------------------------------------------------------------------------------------------------
bin/Image.cpp.o: ./Source/Image/Image.cpp
	@echo [#] Compiling file ./Source/Image/Image.cpp
	g++ -c ./Source/Image/Image.cpp
#-------------------------------------------------------------------------------------------------
bin/BMP.cpp.o: ./Source/Image/BMP/BMP.cpp
	@echo [#] Compiling file ./Source/Image/BMP/BMP.cpp
	g++ -c ./Source/Image/BMP/BMP.cpp
#-------------------------------------------------------------------------------------------------
bin/BMPInfoHeaderType.cpp.o: ./Source/Image/BMP/BMPInfoHeaderType.cpp
	@echo [#] Compiling file ./Source/Image/BMP/BMPInfoHeaderType.cpp
	g++ -c ./Source/Image/BMP/BMPInfoHeaderType.cpp
#-------------------------------------------------------------------------------------------------
bin/BMPType.cpp.o: ./Source/Image/BMP/BMPType.cpp
	@echo [#] Compiling file ./Source/Image/BMP/BMPType.cpp
	g++ -c ./Source/Image/BMP/BMPType.cpp
#-------------------------------------------------------------------------------------------------
bin/BMPInfoHeader.cpp.o: ./Source/Image/BMP/BMPInfoHeader.cpp
	@echo [#] Compiling file ./Source/Image/BMP/BMPInfoHeader.cpp
	g++ -c ./Source/Image/BMP/BMPInfoHeader.cpp
#-------------------------------------------------------------------------------------------------
bin/TGAImageDataType.cpp.o: ./Source/Image/TGA/TGAImageDataType.cpp
	@echo [#] Compiling file ./Source/Image/TGA/TGAImageDataType.cpp
	g++ -c ./Source/Image/TGA/TGAImageDataType.cpp
#-------------------------------------------------------------------------------------------------
bin/TGA.cpp.o: ./Source/Image/TGA/TGA.cpp
	@echo [#] Compiling file ./Source/Image/TGA/TGA.cpp
	g++ -c ./Source/Image/TGA/TGA.cpp
#-------------------------------------------------------------------------------------------------
bin/TGABitsPerPixel.cpp.o: ./Source/Image/TGA/TGABitsPerPixel.cpp
	@echo [#] Compiling file ./Source/Image/TGA/TGABitsPerPixel.cpp
	g++ -c ./Source/Image/TGA/TGABitsPerPixel.cpp
#-------------------------------------------------------------------------------------------------
bin/PNG.cpp.o: ./Source/Image/PNG/PNG.cpp
	@echo [#] Compiling file ./Source/Image/PNG/PNG.cpp
	g++ -c ./Source/Image/PNG/PNG.cpp
#-------------------------------------------------------------------------------------------------
bin/PNGColorCompressor.cpp.o: ./Source/Image/PNG/PNGColorCompressor.cpp
	@echo [#] Compiling file ./Source/Image/PNG/PNGColorCompressor.cpp
	g++ -c ./Source/Image/PNG/PNGColorCompressor.cpp
#-------------------------------------------------------------------------------------------------
bin/PNGColorTree.cpp.o: ./Source/Image/PNG/PNGColorTree.cpp
	@echo [#] Compiling file ./Source/Image/PNG/PNGColorTree.cpp
	g++ -c ./Source/Image/PNG/PNGColorTree.cpp
#-------------------------------------------------------------------------------------------------
bin/PNGTransparency.cpp.o: ./Source/Image/PNG/Chunk/PNGTransparency.cpp
	@echo [#] Compiling file ./Source/Image/PNG/Chunk/PNGTransparency.cpp
	g++ -c ./Source/Image/PNG/Chunk/PNGTransparency.cpp
#-------------------------------------------------------------------------------------------------
bin/PNGColorType.cpp.o: ./Source/Image/PNG/Chunk/PNGColorType.cpp
	@echo [#] Compiling file ./Source/Image/PNG/Chunk/PNGColorType.cpp
	g++ -c ./Source/Image/PNG/Chunk/PNGColorType.cpp
#-------------------------------------------------------------------------------------------------
bin/PNGChunk.cpp.o: ./Source/Image/PNG/Chunk/PNGChunk.cpp
	@echo [#] Compiling file ./Source/Image/PNG/Chunk/PNGChunk.cpp
	g++ -c ./Source/Image/PNG/Chunk/PNGChunk.cpp
#-------------------------------------------------------------------------------------------------
bin/PNGBackgroundColor.cpp.o: ./Source/Image/PNG/Chunk/PNGBackgroundColor.cpp
	@echo [#] Compiling file ./Source/Image/PNG/Chunk/PNGBackgroundColor.cpp
	g++ -c ./Source/Image/PNG/Chunk/PNGBackgroundColor.cpp
#-------------------------------------------------------------------------------------------------
bin/PNGChunkType.cpp.o: ./Source/Image/PNG/Chunk/PNGChunkType.cpp
	@echo [#] Compiling file ./Source/Image/PNG/Chunk/PNGChunkType.cpp
	g++ -c ./Source/Image/PNG/Chunk/PNGChunkType.cpp
#-------------------------------------------------------------------------------------------------
bin/PNGPalette.cpp.o: ./Source/Image/PNG/Chunk/PNGPalette.cpp
	@echo [#] Compiling file ./Source/Image/PNG/Chunk/PNGPalette.cpp
	g++ -c ./Source/Image/PNG/Chunk/PNGPalette.cpp
#-------------------------------------------------------------------------------------------------
bin/PNGInterlaceMethod.cpp.o: ./Source/Image/PNG/Chunk/PNGInterlaceMethod.cpp
	@echo [#] Compiling file ./Source/Image/PNG/Chunk/PNGInterlaceMethod.cpp
	g++ -c ./Source/Image/PNG/Chunk/PNGInterlaceMethod.cpp
#-------------------------------------------------------------------------------------------------
bin/PNGPrimaryChromatics.cpp.o: ./Source/Image/PNG/Chunk/PNGPrimaryChromatics.cpp
	@echo [#] Compiling file ./Source/Image/PNG/Chunk/PNGPrimaryChromatics.cpp
	g++ -c ./Source/Image/PNG/Chunk/PNGPrimaryChromatics.cpp
#-------------------------------------------------------------------------------------------------
bin/PNGPhysicalPixelDimension.cpp.o: ./Source/Image/PNG/Chunk/PNGPhysicalPixelDimension.cpp
	@echo [#] Compiling file ./Source/Image/PNG/Chunk/PNGPhysicalPixelDimension.cpp
	g++ -c ./Source/Image/PNG/Chunk/PNGPhysicalPixelDimension.cpp
#-------------------------------------------------------------------------------------------------
bin/PNGSuggestedPalette.cpp.o: ./Source/Image/PNG/Chunk/PNGSuggestedPalette.cpp
	@echo [#] Compiling file ./Source/Image/PNG/Chunk/PNGSuggestedPalette.cpp
	g++ -c ./Source/Image/PNG/Chunk/PNGSuggestedPalette.cpp
#-------------------------------------------------------------------------------------------------
bin/PNGImageHeader.cpp.o: ./Source/Image/PNG/Chunk/PNGImageHeader.cpp
	@echo [#] Compiling file ./Source/Image/PNG/Chunk/PNGImageHeader.cpp
	g++ -c ./Source/Image/PNG/Chunk/PNGImageHeader.cpp
#-------------------------------------------------------------------------------------------------
bin/PNGLastModificationTime.cpp.o: ./Source/Image/PNG/Chunk/PNGLastModificationTime.cpp
	@echo [#] Compiling file ./Source/Image/PNG/Chunk/PNGLastModificationTime.cpp
	g++ -c ./Source/Image/PNG/Chunk/PNGLastModificationTime.cpp
#-------------------------------------------------------------------------------------------------
bin/PNGPaletteHistogram.cpp.o: ./Source/Image/PNG/Chunk/PNGPaletteHistogram.cpp
	@echo [#] Compiling file ./Source/Image/PNG/Chunk/PNGPaletteHistogram.cpp
	g++ -c ./Source/Image/PNG/Chunk/PNGPaletteHistogram.cpp
#-------------------------------------------------------------------------------------------------
bin/ImageType.cpp.o: ./Source/Image/ImageType.cpp
	@echo [#] Compiling file ./Source/Image/ImageType.cpp
	g++ -c ./Source/Image/ImageType.cpp
#-------------------------------------------------------------------------------------------------
bin/GIF.cpp.o: ./Source/Image/GIF/GIF.cpp
	@echo [#] Compiling file ./Source/Image/GIF/GIF.cpp
	g++ -c ./Source/Image/GIF/GIF.cpp
#-------------------------------------------------------------------------------------------------
bin/ImageDataFormat.cpp.o: ./Source/Image/ImageDataFormat.cpp
	@echo [#] Compiling file ./Source/Image/ImageDataFormat.cpp
	g++ -c ./Source/Image/ImageDataFormat.cpp
#-------------------------------------------------------------------------------------------------
bin/JPEGHuffmanTable.cpp.o: ./Source/Image/JPEG/JPEGHuffmanTable.cpp
	@echo [#] Compiling file ./Source/Image/JPEG/JPEGHuffmanTable.cpp
	g++ -c ./Source/Image/JPEG/JPEGHuffmanTable.cpp
#-------------------------------------------------------------------------------------------------
bin/JPEGScanSelector.cpp.o: ./Source/Image/JPEG/JPEGScanSelector.cpp
	@echo [#] Compiling file ./Source/Image/JPEG/JPEGScanSelector.cpp
	g++ -c ./Source/Image/JPEG/JPEGScanSelector.cpp
#-------------------------------------------------------------------------------------------------
bin/JPEGFileInfo.cpp.o: ./Source/Image/JPEG/JPEGFileInfo.cpp
	@echo [#] Compiling file ./Source/Image/JPEG/JPEGFileInfo.cpp
	g++ -c ./Source/Image/JPEG/JPEGFileInfo.cpp
#-------------------------------------------------------------------------------------------------
bin/JPEG.cpp.o: ./Source/Image/JPEG/JPEG.cpp
	@echo [#] Compiling file ./Source/Image/JPEG/JPEG.cpp
	g++ -c ./Source/Image/JPEG/JPEG.cpp
#-------------------------------------------------------------------------------------------------
bin/JPEGFrame.cpp.o: ./Source/Image/JPEG/JPEGFrame.cpp
	@echo [#] Compiling file ./Source/Image/JPEG/JPEGFrame.cpp
	g++ -c ./Source/Image/JPEG/JPEGFrame.cpp
#-------------------------------------------------------------------------------------------------
bin/JPEGMarker.cpp.o: ./Source/Image/JPEG/JPEGMarker.cpp
	@echo [#] Compiling file ./Source/Image/JPEG/JPEGMarker.cpp
	g++ -c ./Source/Image/JPEG/JPEGMarker.cpp
#-------------------------------------------------------------------------------------------------
bin/JPEGScanStart.cpp.o: ./Source/Image/JPEG/JPEGScanStart.cpp
	@echo [#] Compiling file ./Source/Image/JPEG/JPEGScanStart.cpp
	g++ -c ./Source/Image/JPEG/JPEGScanStart.cpp
#-------------------------------------------------------------------------------------------------
bin/JPEGFrameComponent.cpp.o: ./Source/Image/JPEG/JPEGFrameComponent.cpp
	@echo [#] Compiling file ./Source/Image/JPEG/JPEGFrameComponent.cpp
	g++ -c ./Source/Image/JPEG/JPEGFrameComponent.cpp
#-------------------------------------------------------------------------------------------------
bin/TIFF.cpp.o: ./Source/Image/TIFF/TIFF.cpp
	@echo [#] Compiling file ./Source/Image/TIFF/TIFF.cpp
	g++ -c ./Source/Image/TIFF/TIFF.cpp
#-------------------------------------------------------------------------------------------------
bin/ISBN.cpp.o: ./Source/Algorithm/ISBN.cpp
	@echo [#] Compiling file ./Source/Algorithm/ISBN.cpp
	g++ -c ./Source/Algorithm/ISBN.cpp
#-------------------------------------------------------------------------------------------------
bin/CRC32.cpp.o: ./Source/Algorithm/CRC32.cpp
	@echo [#] Compiling file ./Source/Algorithm/CRC32.cpp
	g++ -c ./Source/Algorithm/CRC32.cpp
#-------------------------------------------------------------------------------------------------
bin/Adler32.cpp.o: ./Source/Algorithm/Adler32.cpp
	@echo [#] Compiling file ./Source/Algorithm/Adler32.cpp
	g++ -c ./Source/Algorithm/Adler32.cpp
#-------------------------------------------------------------------------------------------------
bin/AsyncLock.cpp.o: ./Source/Async/AsyncLock.cpp
	@echo [#] Compiling file ./Source/Async/AsyncLock.cpp
	g++ -c ./Source/Async/AsyncLock.cpp
#-------------------------------------------------------------------------------------------------
bin/Thread.cpp.o: ./Source/Async/Thread.cpp
	@echo [#] Compiling file ./Source/Async/Thread.cpp
	g++ -c ./Source/Async/Thread.cpp
#-------------------------------------------------------------------------------------------------
bin/ErrorCode.cpp.o: ./Source/ErrorCode.cpp
	@echo [#] Compiling file ./Source/ErrorCode.cpp
	g++ -c ./Source/ErrorCode.cpp
#-------------------------------------------------------------------------------------------------
bin/UUID.cpp.o: ./Source/Types/UUID.cpp
	@echo [#] Compiling file ./Source/Types/UUID.cpp
	g++ -c ./Source/Types/UUID.cpp
#-------------------------------------------------------------------------------------------------
bin/StopWatch.cpp.o: ./Source/Time/StopWatch.cpp
	@echo [#] Compiling file ./Source/Time/StopWatch.cpp
	g++ -c ./Source/Time/StopWatch.cpp
#-------------------------------------------------------------------------------------------------
bin/SocketActionResult.cpp.o: ./Source/Network/SocketActionResult.cpp
	@echo [#] Compiling file ./Source/Network/SocketActionResult.cpp
	g++ -c ./Source/Network/SocketActionResult.cpp
#-------------------------------------------------------------------------------------------------
bin/IClientListener.hpp.o: ./Source/Network/IClientListener.hpp
	@echo [#] Compiling file ./Source/Network/IClientListener.hpp
	g++ -c ./Source/Network/IClientListener.hpp
#-------------------------------------------------------------------------------------------------
bin/Client.cpp.o: ./Source/Network/Client.cpp
	@echo [#] Compiling file ./Source/Network/Client.cpp
	g++ -c ./Source/Network/Client.cpp
#-------------------------------------------------------------------------------------------------
bin/ProtocolMode.cpp.o: ./Source/Network/ProtocolMode.cpp
	@echo [#] Compiling file ./Source/Network/ProtocolMode.cpp
	g++ -c ./Source/Network/ProtocolMode.cpp
#-------------------------------------------------------------------------------------------------
bin/IPAdressInfo.cpp.o: ./Source/Network/IPAdressInfo.cpp
	@echo [#] Compiling file ./Source/Network/IPAdressInfo.cpp
	g++ -c ./Source/Network/IPAdressInfo.cpp
#-------------------------------------------------------------------------------------------------
bin/ServerListeningThreadInfo.cpp.o: ./Source/Network/ServerListeningThreadInfo.cpp
	@echo [#] Compiling file ./Source/Network/ServerListeningThreadInfo.cpp
	g++ -c ./Source/Network/ServerListeningThreadInfo.cpp
#-------------------------------------------------------------------------------------------------
bin/IOSocket.cpp.o: ./Source/Network/IOSocket.cpp
	@echo [#] Compiling file ./Source/Network/IOSocket.cpp
	g++ -c ./Source/Network/IOSocket.cpp
#-------------------------------------------------------------------------------------------------
bin/Server.cpp.o: ./Source/Network/Server.cpp
	@echo [#] Compiling file ./Source/Network/Server.cpp
	g++ -c ./Source/Network/Server.cpp
#-------------------------------------------------------------------------------------------------
bin/IOSocketMessage.cpp.o: ./Source/Network/IOSocketMessage.cpp
	@echo [#] Compiling file ./Source/Network/IOSocketMessage.cpp
	g++ -c ./Source/Network/IOSocketMessage.cpp
#-------------------------------------------------------------------------------------------------
bin/SocketType.cpp.o: ./Source/Network/SocketType.cpp
	@echo [#] Compiling file ./Source/Network/SocketType.cpp
	g++ -c ./Source/Network/SocketType.cpp
#-------------------------------------------------------------------------------------------------
bin/IPVersion.cpp.o: ./Source/Network/IPVersion.cpp
	@echo [#] Compiling file ./Source/Network/IPVersion.cpp
	g++ -c ./Source/Network/IPVersion.cpp
#-------------------------------------------------------------------------------------------------
bin/IPAdressFamily.cpp.o: ./Source/Network/IPAdressFamily.cpp
	@echo [#] Compiling file ./Source/Network/IPAdressFamily.cpp
	g++ -c ./Source/Network/IPAdressFamily.cpp
#########################################
