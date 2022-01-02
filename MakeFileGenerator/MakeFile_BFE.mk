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
$(DirTemp)/SystemPhysics.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\Collision\SystemPhysics.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\Collision\SystemPhysics.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\Collision\SystemPhysics.cpp" -o $(DirTemp)/SystemPhysics.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Entity.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\Entity\Entity.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\Entity\Entity.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\Entity\Entity.cpp" -o $(DirTemp)/Entity.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Player.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\Player\Player.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\Player\Player.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\Player\Player.cpp" -o $(DirTemp)/Player.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ResouceManager.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\Resource\ResouceManager.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\Resource\ResouceManager.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\Resource\ResouceManager.cpp" -o $(DirTemp)/ResouceManager.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/BitFireEngine.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\System\BitFireEngine.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\System\BitFireEngine.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\System\BitFireEngine.cpp" -o $(DirTemp)/BitFireEngine.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IBitFireEngineListener.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\System\IBitFireEngineListener.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\System\IBitFireEngineListener.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\System\IBitFireEngineListener.hpp" -o $(DirTemp)/IBitFireEngineListener.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IBitFireEngineRenderListener.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\System\IBitFireEngineRenderListener.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\System\IBitFireEngineRenderListener.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\System\IBitFireEngineRenderListener.hpp" -o $(DirTemp)/IBitFireEngineRenderListener.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IBitFireEngineSoundListener.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\System\IBitFireEngineSoundListener.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\System\IBitFireEngineSoundListener.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\System\IBitFireEngineSoundListener.hpp" -o $(DirTemp)/IBitFireEngineSoundListener.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/UIDialogBox.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\UI\DialogBox\UIDialogBox.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\UI\DialogBox\UIDialogBox.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\UI\DialogBox\UIDialogBox.cpp" -o $(DirTemp)/UIDialogBox.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/UIButton.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\UI\UIButton.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\UI\UIButton.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\UI\UIButton.cpp" -o $(DirTemp)/UIButton.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/UIElement.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\UI\UIElement.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\UI\UIElement.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\UI\UIElement.cpp" -o $(DirTemp)/UIElement.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/UIImage.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\UI\UIImage.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\UI\UIImage.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\UI\UIImage.cpp" -o $(DirTemp)/UIImage.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/UIText.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\UI\UIText.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\UI\UIText.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngine\Source\UI\UIText.cpp" -o $(DirTemp)/UIText.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/BitFireEngineIDE.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngineIDE\BitFireEngineIDE.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngineIDE\BitFireEngineIDE.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\BitFireEngineIDE\BitFireEngineIDE.cpp" -o $(DirTemp)/BitFireEngineIDE.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/CleavedGameSystem.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\GameCleaved\Source\CleavedGameSystem.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\GameCleaved\Source\CleavedGameSystem.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\GameCleaved\Source\CleavedGameSystem.cpp" -o $(DirTemp)/CleavedGameSystem.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Main.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\GameCleaved\Source\Main.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\GameCleaved\Source\Main.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\GameCleaved\Source\Main.cpp" -o $(DirTemp)/Main.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Main.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\GameZEE\Source\Main.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\GameZEE\Source\Main.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\GameZEE\Source\Main.cpp" -o $(DirTemp)/Main.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ZEEGameSystem.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\GameZEE\Source\ZEEGameSystem.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\GameZEE\Source\ZEEGameSystem.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\GameZEE\Source\ZEEGameSystem.cpp" -o $(DirTemp)/ZEEGameSystem.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MakeFileGenerator.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\MakeFileGenerator\MakeFileGenerator.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\MakeFileGenerator\MakeFileGenerator.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\MakeFileGenerator\MakeFileGenerator.cpp" -o $(DirTemp)/MakeFileGenerator.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/InputButton.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Device\InputButton.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Device\InputButton.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Device\InputButton.cpp" -o $(DirTemp)/InputButton.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/InputContainer.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Device\InputContainer.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Device\InputContainer.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Device\InputContainer.cpp" -o $(DirTemp)/InputContainer.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/InputSystem.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Device\InputSystem.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Device\InputSystem.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Device\InputSystem.cpp" -o $(DirTemp)/InputSystem.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/KeyBoard.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Device\KeyBoard\KeyBoard.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Device\KeyBoard\KeyBoard.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Device\KeyBoard\KeyBoard.cpp" -o $(DirTemp)/KeyBoard.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Mouse.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Device\Mouse\Mouse.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Device\Mouse\Mouse.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Device\Mouse\Mouse.cpp" -o $(DirTemp)/Mouse.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/OpenGLAPI.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\OpenGLAPI.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\OpenGLAPI.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\OpenGLAPI.cpp" -o $(DirTemp)/OpenGLAPI.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/VideoConfig.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\VideoConfig.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\VideoConfig.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\VideoConfig.cpp" -o $(DirTemp)/VideoConfig.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/VulcanAPI.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\VulcanAPI.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\VulcanAPI.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\VulcanAPI.cpp" -o $(DirTemp)/VulcanAPI.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Key.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Window\Key.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Window\Key.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Window\Key.cpp" -o $(DirTemp)/Key.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Window.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Window\Window.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Window\Window.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemRender\Source\Window\Window.cpp" -o $(DirTemp)/Window.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Adler32.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Algorithm\Adler32.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Algorithm\Adler32.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Algorithm\Adler32.cpp" -o $(DirTemp)/Adler32.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/CRC32.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Algorithm\CRC32.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Algorithm\CRC32.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Algorithm\CRC32.cpp" -o $(DirTemp)/CRC32.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ISBN.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Algorithm\ISBN.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Algorithm\ISBN.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Algorithm\ISBN.cpp" -o $(DirTemp)/ISBN.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/AsyncLock.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Async\AsyncLock.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Async\AsyncLock.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Async\AsyncLock.cpp" -o $(DirTemp)/AsyncLock.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Thread.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Async\Thread.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Async\Thread.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Async\Thread.cpp" -o $(DirTemp)/Thread.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Camera.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Camera\Camera.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Camera\Camera.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Camera\Camera.cpp" -o $(DirTemp)/Camera.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/CameraPerspective.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Camera\CameraPerspective.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Camera\CameraPerspective.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Camera\CameraPerspective.hpp" -o $(DirTemp)/CameraPerspective.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ADAM7.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\ADAM7\ADAM7.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\ADAM7\ADAM7.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\ADAM7\ADAM7.cpp" -o $(DirTemp)/ADAM7.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/DeflateBlock.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\DEFLATE\DeflateBlock.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\DEFLATE\DeflateBlock.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\DEFLATE\DeflateBlock.cpp" -o $(DirTemp)/DeflateBlock.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/DeflateEncodingMethod.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\DEFLATE\DeflateEncodingMethod.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\DEFLATE\DeflateEncodingMethod.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\DEFLATE\DeflateEncodingMethod.cpp" -o $(DirTemp)/DeflateEncodingMethod.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/HuffmanCodeType.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\HUFFMAN\HuffmanCodeType.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\HUFFMAN\HuffmanCodeType.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\HUFFMAN\HuffmanCodeType.cpp" -o $(DirTemp)/HuffmanCodeType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/HuffmanNumberCode.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\HUFFMAN\HuffmanNumberCode.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\HUFFMAN\HuffmanNumberCode.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\HUFFMAN\HuffmanNumberCode.cpp" -o $(DirTemp)/HuffmanNumberCode.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/HuffmanSymbol.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\HUFFMAN\HuffmanSymbol.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\HUFFMAN\HuffmanSymbol.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\HUFFMAN\HuffmanSymbol.cpp" -o $(DirTemp)/HuffmanSymbol.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/HuffmanTree.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\HUFFMAN\HuffmanTree.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\HUFFMAN\HuffmanTree.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\HUFFMAN\HuffmanTree.cpp" -o $(DirTemp)/HuffmanTree.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ZLIB.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\ZLIB\ZLIB.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\ZLIB\ZLIB.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\ZLIB\ZLIB.cpp" -o $(DirTemp)/ZLIB.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ZLIBCompressionLevel.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\ZLIB\ZLIBCompressionLevel.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\ZLIB\ZLIBCompressionLevel.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\ZLIB\ZLIBCompressionLevel.cpp" -o $(DirTemp)/ZLIBCompressionLevel.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ZLIBCompressionMethod.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\ZLIB\ZLIBCompressionMethod.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\ZLIB\ZLIBCompressionMethod.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\ZLIB\ZLIBCompressionMethod.cpp" -o $(DirTemp)/ZLIBCompressionMethod.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ZLIBHeader.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\ZLIB\ZLIBHeader.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\ZLIB\ZLIBHeader.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Compression\ZLIB\ZLIBHeader.cpp" -o $(DirTemp)/ZLIBHeader.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/AsciiString.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\AsciiString.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\AsciiString.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\AsciiString.cpp" -o $(DirTemp)/AsciiString.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/BinaryTree.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\BinaryTree\BinaryTree.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\BinaryTree\BinaryTree.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\BinaryTree\BinaryTree.hpp" -o $(DirTemp)/BinaryTree.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/BinaryTreeData.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\BinaryTree\BinaryTreeData.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\BinaryTree\BinaryTreeData.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\BinaryTree\BinaryTreeData.hpp" -o $(DirTemp)/BinaryTreeData.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/BinaryTreeNode.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\BinaryTree\BinaryTreeNode.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\BinaryTree\BinaryTreeNode.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\BinaryTree\BinaryTreeNode.hpp" -o $(DirTemp)/BinaryTreeNode.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/BitStreamHusk.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\BitStreamHusk.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\BitStreamHusk.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\BitStreamHusk.cpp" -o $(DirTemp)/BitStreamHusk.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Dictionary.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\Dictionary.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\Dictionary.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\Dictionary.hpp" -o $(DirTemp)/Dictionary.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/DictionaryStatic.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\DictionaryStatic.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\DictionaryStatic.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\DictionaryStatic.hpp" -o $(DirTemp)/DictionaryStatic.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/LinkedList.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\LinkedList.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\LinkedList.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\LinkedList.hpp" -o $(DirTemp)/LinkedList.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/LinkedListNode.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\LinkedListNode.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\LinkedListNode.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\LinkedListNode.hpp" -o $(DirTemp)/LinkedListNode.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/List.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\List.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\List.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\List.hpp" -o $(DirTemp)/List.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/QuadTree.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\QuadTree\QuadTree.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\QuadTree\QuadTree.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\QuadTree\QuadTree.hpp" -o $(DirTemp)/QuadTree.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/QuadTreeDirection.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\QuadTree\QuadTreeDirection.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\QuadTree\QuadTreeDirection.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\QuadTree\QuadTreeDirection.hpp" -o $(DirTemp)/QuadTreeDirection.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/QuadTreeNode.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\QuadTree\QuadTreeNode.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\QuadTree\QuadTreeNode.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\QuadTree\QuadTreeNode.hpp" -o $(DirTemp)/QuadTreeNode.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/QuadTreePosition.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\QuadTree\QuadTreePosition.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\QuadTree\QuadTreePosition.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\QuadTree\QuadTreePosition.hpp" -o $(DirTemp)/QuadTreePosition.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Queue.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\Queue.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\Queue.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\Queue.hpp" -o $(DirTemp)/Queue.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/RingBuffer.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\RingBuffer.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\RingBuffer.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\RingBuffer.hpp" -o $(DirTemp)/RingBuffer.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Table.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\Table.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\Table.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Container\Table.hpp" -o $(DirTemp)/Table.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Dialog.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Dialog\Dialog.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Dialog\Dialog.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Dialog\Dialog.cpp" -o $(DirTemp)/Dialog.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/EML.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Email\EML.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Email\EML.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Email\EML.cpp" -o $(DirTemp)/EML.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Caesar.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Encryption\Caesar.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Encryption\Caesar.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Encryption\Caesar.cpp" -o $(DirTemp)/Caesar.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ICypher.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Encryption\ICypher.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Encryption\ICypher.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Encryption\ICypher.cpp" -o $(DirTemp)/ICypher.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/RSA.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Encryption\RSA.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Encryption\RSA.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Encryption\RSA.cpp" -o $(DirTemp)/RSA.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ErrorCode.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\ErrorCode.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\ErrorCode.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\ErrorCode.cpp" -o $(DirTemp)/ErrorCode.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Event.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Event\Event.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Event\Event.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Event\Event.hpp" -o $(DirTemp)/Event.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Bash.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\Bash.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\Bash.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\Bash.cpp" -o $(DirTemp)/Bash.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ByteStream.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\ByteStream.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\ByteStream.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\ByteStream.cpp" -o $(DirTemp)/ByteStream.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/File.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\File.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\File.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\File.cpp" -o $(DirTemp)/File.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FileActionResult.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\FileActionResult.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\FileActionResult.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\FileActionResult.hpp" -o $(DirTemp)/FileActionResult.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FileOpenMode.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\FileOpenMode.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\FileOpenMode.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\FileOpenMode.hpp" -o $(DirTemp)/FileOpenMode.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FilePersistence.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\FilePersistence.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\FilePersistence.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\FilePersistence.hpp" -o $(DirTemp)/FilePersistence.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FileStream.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\FileStream.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\FileStream.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\FileStream.cpp" -o $(DirTemp)/FileStream.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FileTemporary.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\FileTemporary.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\FileTemporary.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\FileTemporary.cpp" -o $(DirTemp)/FileTemporary.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IFIle.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\IFIle.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\IFIle.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\IFIle.cpp" -o $(DirTemp)/IFIle.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/OpenFileDialog.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\OpenFileDialog.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\OpenFileDialog.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\OpenFileDialog.cpp" -o $(DirTemp)/OpenFileDialog.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Program.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\Program.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\Program.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\Program.cpp" -o $(DirTemp)/Program.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ProgramExecuteInfo.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\ProgramExecuteInfo.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\ProgramExecuteInfo.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\ProgramExecuteInfo.cpp" -o $(DirTemp)/ProgramExecuteInfo.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ProgramExecuteResultListener.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\ProgramExecuteResultListener.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\ProgramExecuteResultListener.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\File\ProgramExecuteResultListener.hpp" -o $(DirTemp)/ProgramExecuteResultListener.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FNT.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\FNT\FNT.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\FNT\FNT.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\FNT\FNT.cpp" -o $(DirTemp)/FNT.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FNTCharacter.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\FNT\FNTCharacter.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\FNT\FNTCharacter.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\FNT\FNTCharacter.cpp" -o $(DirTemp)/FNTCharacter.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FNTCommonData.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\FNT\FNTCommonData.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\FNT\FNTCommonData.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\FNT\FNTCommonData.cpp" -o $(DirTemp)/FNTCommonData.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FNTInfo.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\FNT\FNTInfo.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\FNT\FNTInfo.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\FNT\FNTInfo.cpp" -o $(DirTemp)/FNTInfo.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FNTPage.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\FNT\FNTPage.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\FNT\FNTPage.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\FNT\FNTPage.cpp" -o $(DirTemp)/FNTPage.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Font.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\Font.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\Font.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\Font.cpp" -o $(DirTemp)/Font.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IFontFormat.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\IFontFormat.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\IFontFormat.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\IFontFormat.hpp" -o $(DirTemp)/IFontFormat.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/OTF.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\OTF\OTF.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\OTF\OTF.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\OTF\OTF.cpp" -o $(DirTemp)/OTF.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/EncodingID.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\CMAP\EncodingID.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\CMAP\EncodingID.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\CMAP\EncodingID.cpp" -o $(DirTemp)/EncodingID.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/EncodingRecord.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\CMAP\EncodingRecord.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\CMAP\EncodingRecord.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\CMAP\EncodingRecord.cpp" -o $(DirTemp)/EncodingRecord.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PlatformID.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\CMAP\PlatformID.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\CMAP\PlatformID.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\CMAP\PlatformID.cpp" -o $(DirTemp)/PlatformID.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFCharacterMapping.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\CMAP\TTFCharacterMapping.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\CMAP\TTFCharacterMapping.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\CMAP\TTFCharacterMapping.cpp" -o $(DirTemp)/TTFCharacterMapping.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFDigitalSignature.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\DSIG\TTFDigitalSignature.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\DSIG\TTFDigitalSignature.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\DSIG\TTFDigitalSignature.cpp" -o $(DirTemp)/TTFDigitalSignature.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFDigitalSignatureBlock.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\DSIG\TTFDigitalSignatureBlock.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\DSIG\TTFDigitalSignatureBlock.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\DSIG\TTFDigitalSignatureBlock.cpp" -o $(DirTemp)/TTFDigitalSignatureBlock.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFDigitalSignatureRecord.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\DSIG\TTFDigitalSignatureRecord.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\DSIG\TTFDigitalSignatureRecord.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\DSIG\TTFDigitalSignatureRecord.cpp" -o $(DirTemp)/TTFDigitalSignatureRecord.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFKerning.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\KERN\TTFKerning.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\KERN\TTFKerning.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\KERN\TTFKerning.cpp" -o $(DirTemp)/TTFKerning.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFKerningPair.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\KERN\TTFKerningPair.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\KERN\TTFKerningPair.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\KERN\TTFKerningPair.cpp" -o $(DirTemp)/TTFKerningPair.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFKerningSubtable.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\KERN\TTFKerningSubtable.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\KERN\TTFKerningSubtable.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\KERN\TTFKerningSubtable.cpp" -o $(DirTemp)/TTFKerningSubtable.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFSubtableFormat0.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\KERN\TTFSubtableFormat0.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\KERN\TTFSubtableFormat0.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\KERN\TTFSubtableFormat0.cpp" -o $(DirTemp)/TTFSubtableFormat0.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFSubtableFormat2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\KERN\TTFSubtableFormat2.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\KERN\TTFSubtableFormat2.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\KERN\TTFSubtableFormat2.cpp" -o $(DirTemp)/TTFSubtableFormat2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFArmStyle.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFArmStyle.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFArmStyle.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFArmStyle.cpp" -o $(DirTemp)/TTFArmStyle.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFContrast.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFContrast.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFContrast.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFContrast.cpp" -o $(DirTemp)/TTFContrast.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFFamilyType.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFFamilyType.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFFamilyType.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFFamilyType.cpp" -o $(DirTemp)/TTFFamilyType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFHeightX.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFHeightX.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFHeightX.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFHeightX.cpp" -o $(DirTemp)/TTFHeightX.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFLetterform.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFLetterform.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFLetterform.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFLetterform.cpp" -o $(DirTemp)/TTFLetterform.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFMidline.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFMidline.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFMidline.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFMidline.cpp" -o $(DirTemp)/TTFMidline.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFPanose.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFPanose.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFPanose.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFPanose.cpp" -o $(DirTemp)/TTFPanose.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFProportion.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFProportion.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFProportion.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFProportion.cpp" -o $(DirTemp)/TTFProportion.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFSerifStyle.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFSerifStyle.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFSerifStyle.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFSerifStyle.cpp" -o $(DirTemp)/TTFSerifStyle.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFStrokeVariatoon.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFStrokeVariatoon.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFStrokeVariatoon.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFStrokeVariatoon.cpp" -o $(DirTemp)/TTFStrokeVariatoon.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFWeight.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFWeight.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFWeight.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\Panose\TTFWeight.cpp" -o $(DirTemp)/TTFWeight.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFCompatibility.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\TTFCompatibility.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\TTFCompatibility.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\OS2\TTFCompatibility.cpp" -o $(DirTemp)/TTFCompatibility.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFHeader.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFHeader.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFHeader.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFHeader.cpp" -o $(DirTemp)/TTFHeader.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFHorizontalHeader.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFHorizontalHeader.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFHorizontalHeader.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFHorizontalHeader.cpp" -o $(DirTemp)/TTFHorizontalHeader.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFLinearThreshold.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFLinearThreshold.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFLinearThreshold.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFLinearThreshold.cpp" -o $(DirTemp)/TTFLinearThreshold.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFMaximumProfile.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFMaximumProfile.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFMaximumProfile.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFMaximumProfile.cpp" -o $(DirTemp)/TTFMaximumProfile.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFOffsetTable.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFOffsetTable.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFOffsetTable.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFOffsetTable.cpp" -o $(DirTemp)/TTFOffsetTable.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFPostScript.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFPostScript.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFPostScript.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFPostScript.cpp" -o $(DirTemp)/TTFPostScript.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFVersion.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFVersion.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFVersion.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFVersion.cpp" -o $(DirTemp)/TTFVersion.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFVersionType.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFVersionType.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFVersionType.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFVersionType.cpp" -o $(DirTemp)/TTFVersionType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFVerticalDeviceMetrics.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFVerticalDeviceMetrics.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFVerticalDeviceMetrics.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\Chunks\TTFVerticalDeviceMetrics.cpp" -o $(DirTemp)/TTFVerticalDeviceMetrics.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTF.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\TTF.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\TTF.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\TTF.cpp" -o $(DirTemp)/TTF.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFTableEntry.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\TTFTableEntry.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\TTFTableEntry.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\TTFTableEntry.cpp" -o $(DirTemp)/TTFTableEntry.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TTFTableEntryType.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\TTFTableEntryType.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\TTFTableEntryType.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Font\TTF\TTFTableEntryType.cpp" -o $(DirTemp)/TTFTableEntryType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/SkyBox.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Game\SkyBox.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Game\SkyBox.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Game\SkyBox.cpp" -o $(DirTemp)/SkyBox.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Sprite.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Game\Sprite.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Game\Sprite.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Game\Sprite.cpp" -o $(DirTemp)/Sprite.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IFileFormat.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\IFileFormat.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\IFileFormat.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\IFileFormat.hpp" -o $(DirTemp)/IFileFormat.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/BMP.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\BMP\BMP.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\BMP\BMP.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\BMP\BMP.cpp" -o $(DirTemp)/BMP.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/BMPInfoHeader.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\BMP\BMPInfoHeader.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\BMP\BMPInfoHeader.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\BMP\BMPInfoHeader.cpp" -o $(DirTemp)/BMPInfoHeader.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/BMPInfoHeaderType.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\BMP\BMPInfoHeaderType.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\BMP\BMPInfoHeaderType.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\BMP\BMPInfoHeaderType.cpp" -o $(DirTemp)/BMPInfoHeaderType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/BMPType.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\BMP\BMPType.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\BMP\BMPType.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\BMP\BMPType.cpp" -o $(DirTemp)/BMPType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/GIF.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\GIF\GIF.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\GIF\GIF.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\GIF\GIF.cpp" -o $(DirTemp)/GIF.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Image.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\Image.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\Image.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\Image.cpp" -o $(DirTemp)/Image.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ImageDataFormat.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\ImageDataFormat.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\ImageDataFormat.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\ImageDataFormat.cpp" -o $(DirTemp)/ImageDataFormat.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ImageType.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\ImageType.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\ImageType.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\ImageType.cpp" -o $(DirTemp)/ImageType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/JPEG.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEG.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEG.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEG.cpp" -o $(DirTemp)/JPEG.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/JPEGFileInfo.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGFileInfo.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGFileInfo.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGFileInfo.cpp" -o $(DirTemp)/JPEGFileInfo.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/JPEGFrame.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGFrame.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGFrame.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGFrame.cpp" -o $(DirTemp)/JPEGFrame.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/JPEGFrameComponent.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGFrameComponent.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGFrameComponent.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGFrameComponent.cpp" -o $(DirTemp)/JPEGFrameComponent.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/JPEGHuffmanTable.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGHuffmanTable.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGHuffmanTable.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGHuffmanTable.cpp" -o $(DirTemp)/JPEGHuffmanTable.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/JPEGMarker.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGMarker.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGMarker.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGMarker.cpp" -o $(DirTemp)/JPEGMarker.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/JPEGScanSelector.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGScanSelector.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGScanSelector.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGScanSelector.cpp" -o $(DirTemp)/JPEGScanSelector.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/JPEGScanStart.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGScanStart.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGScanStart.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\JPEG\JPEGScanStart.cpp" -o $(DirTemp)/JPEGScanStart.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGBackgroundColor.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGBackgroundColor.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGBackgroundColor.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGBackgroundColor.cpp" -o $(DirTemp)/PNGBackgroundColor.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGChunk.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGChunk.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGChunk.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGChunk.cpp" -o $(DirTemp)/PNGChunk.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGChunkType.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGChunkType.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGChunkType.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGChunkType.cpp" -o $(DirTemp)/PNGChunkType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGColorType.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGColorType.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGColorType.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGColorType.cpp" -o $(DirTemp)/PNGColorType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGImageHeader.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGImageHeader.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGImageHeader.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGImageHeader.cpp" -o $(DirTemp)/PNGImageHeader.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGInterlaceMethod.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGInterlaceMethod.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGInterlaceMethod.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGInterlaceMethod.cpp" -o $(DirTemp)/PNGInterlaceMethod.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGLastModificationTime.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGLastModificationTime.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGLastModificationTime.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGLastModificationTime.cpp" -o $(DirTemp)/PNGLastModificationTime.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGPalette.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGPalette.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGPalette.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGPalette.cpp" -o $(DirTemp)/PNGPalette.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGPaletteHistogram.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGPaletteHistogram.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGPaletteHistogram.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGPaletteHistogram.cpp" -o $(DirTemp)/PNGPaletteHistogram.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGPhysicalPixelDimension.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGPhysicalPixelDimension.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGPhysicalPixelDimension.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGPhysicalPixelDimension.cpp" -o $(DirTemp)/PNGPhysicalPixelDimension.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGPrimaryChromatics.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGPrimaryChromatics.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGPrimaryChromatics.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGPrimaryChromatics.cpp" -o $(DirTemp)/PNGPrimaryChromatics.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGSuggestedPalette.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGSuggestedPalette.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGSuggestedPalette.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGSuggestedPalette.cpp" -o $(DirTemp)/PNGSuggestedPalette.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGTransparency.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGTransparency.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGTransparency.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\Chunk\PNGTransparency.cpp" -o $(DirTemp)/PNGTransparency.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNG.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\PNG.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\PNG.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\PNG.cpp" -o $(DirTemp)/PNG.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGColorCompressor.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\PNGColorCompressor.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\PNGColorCompressor.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\PNGColorCompressor.cpp" -o $(DirTemp)/PNGColorCompressor.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PNGColorTree.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\PNGColorTree.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\PNGColorTree.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\PNG\PNGColorTree.cpp" -o $(DirTemp)/PNGColorTree.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TGA.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\TGA\TGA.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\TGA\TGA.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\TGA\TGA.cpp" -o $(DirTemp)/TGA.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TGABitsPerPixel.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\TGA\TGABitsPerPixel.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\TGA\TGABitsPerPixel.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\TGA\TGABitsPerPixel.cpp" -o $(DirTemp)/TGABitsPerPixel.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TGAImageDataType.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\TGA\TGAImageDataType.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\TGA\TGAImageDataType.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\TGA\TGAImageDataType.cpp" -o $(DirTemp)/TGAImageDataType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TIFF.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\TIFF\TIFF.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\TIFF\TIFF.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Image\TIFF\TIFF.cpp" -o $(DirTemp)/TIFF.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Level.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Level\Level.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Level\Level.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Level\Level.cpp" -o $(DirTemp)/Level.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/BoxPlot.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Diagrams\BoxPlot.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Diagrams\BoxPlot.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Diagrams\BoxPlot.hpp" -o $(DirTemp)/BoxPlot.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/AngleDegree.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\AngleDegree.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\AngleDegree.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\AngleDegree.hpp" -o $(DirTemp)/AngleDegree.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/AngleRadians.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\AngleRadians.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\AngleRadians.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\AngleRadians.hpp" -o $(DirTemp)/AngleRadians.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Cone.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Cone.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Cone.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Cone.cpp" -o $(DirTemp)/Cone.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Cube.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Cube.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Cube.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Cube.cpp" -o $(DirTemp)/Cube.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Cuboid.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Cuboid.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Cuboid.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Cuboid.cpp" -o $(DirTemp)/Cuboid.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Cylinder.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Cylinder.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Cylinder.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Cylinder.cpp" -o $(DirTemp)/Cylinder.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Form.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Form.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Form.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Form.cpp" -o $(DirTemp)/Form.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Icosahedron.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Icosahedron.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Icosahedron.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Icosahedron.cpp" -o $(DirTemp)/Icosahedron.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Sphere.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Sphere.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Sphere.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\Sphere.cpp" -o $(DirTemp)/Sphere.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/SquarePyramid.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\SquarePyramid.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\SquarePyramid.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Form\SquarePyramid.cpp" -o $(DirTemp)/SquarePyramid.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Matrix.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Matrix.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Matrix.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Matrix.hpp" -o $(DirTemp)/Matrix.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Matrix2x2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Matrix2x2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Matrix2x2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Matrix2x2.hpp" -o $(DirTemp)/Matrix2x2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Matrix3x3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Matrix3x3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Matrix3x3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Matrix3x3.hpp" -o $(DirTemp)/Matrix3x3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Matrix4x4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Matrix4x4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Matrix4x4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Matrix4x4.hpp" -o $(DirTemp)/Matrix4x4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Padding.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Padding.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Padding.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Padding.hpp" -o $(DirTemp)/Padding.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Circle.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Circle.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Circle.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Circle.cpp" -o $(DirTemp)/Circle.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Hexagon.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Hexagon.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Hexagon.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Hexagon.cpp" -o $(DirTemp)/Hexagon.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Pentagon.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Pentagon.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Pentagon.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Pentagon.cpp" -o $(DirTemp)/Pentagon.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Rectangle.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Rectangle.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Rectangle.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Rectangle.cpp" -o $(DirTemp)/Rectangle.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Shape.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Shape.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Shape.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Shape.cpp" -o $(DirTemp)/Shape.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Square.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Square.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Square.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Square.cpp" -o $(DirTemp)/Square.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Star.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Star.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Star.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Star.cpp" -o $(DirTemp)/Star.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Triangle.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Triangle.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Triangle.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Shape\Triangle.cpp" -o $(DirTemp)/Triangle.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Vector2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Vector2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Vector2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Vector2.hpp" -o $(DirTemp)/Vector2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Vector3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Vector3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Vector3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Vector3.hpp" -o $(DirTemp)/Vector3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Vector4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Vector4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Vector4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Geometry\Vector4.hpp" -o $(DirTemp)/Vector4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Interpolate.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Interpolate.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Interpolate.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Interpolate.cpp" -o $(DirTemp)/Interpolate.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Math.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Math.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Math.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Math.cpp" -o $(DirTemp)/Math.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Collider.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Physic\Collider.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Physic\Collider.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Physic\Collider.cpp" -o $(DirTemp)/Collider.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/GravityCube.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Physic\GravityCube.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Physic\GravityCube.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Physic\GravityCube.cpp" -o $(DirTemp)/GravityCube.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/GravityField.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Physic\GravityField.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Physic\GravityField.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Physic\GravityField.cpp" -o $(DirTemp)/GravityField.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/GravitySphere.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Physic\GravitySphere.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Physic\GravitySphere.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Physic\GravitySphere.cpp" -o $(DirTemp)/GravitySphere.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PhysicsDynamic.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Physic\PhysicsDynamic.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Physic\PhysicsDynamic.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Physic\PhysicsDynamic.hpp" -o $(DirTemp)/PhysicsDynamic.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PhysicsStatic.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Physic\PhysicsStatic.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Physic\PhysicsStatic.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Math\Physic\PhysicsStatic.hpp" -o $(DirTemp)/PhysicsStatic.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/A3DS.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\3DS\A3DS.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\3DS\A3DS.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\3DS\A3DS.cpp" -o $(DirTemp)/A3DS.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FBX.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\FBX\FBX.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\FBX\FBX.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\FBX\FBX.cpp" -o $(DirTemp)/FBX.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IModelFormat.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\IModelFormat.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\IModelFormat.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\IModelFormat.hpp" -o $(DirTemp)/IModelFormat.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/LinkedMesh.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\LinkedMesh.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\LinkedMesh.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\LinkedMesh.cpp" -o $(DirTemp)/LinkedMesh.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Material.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\Material.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\Material.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\Material.cpp" -o $(DirTemp)/Material.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Mesh.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\Mesh.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\Mesh.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\Mesh.cpp" -o $(DirTemp)/Mesh.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MeshIndexData.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\MeshIndexData.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\MeshIndexData.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\MeshIndexData.cpp" -o $(DirTemp)/MeshIndexData.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MeshRenderInfo.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\MeshRenderInfo.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\MeshRenderInfo.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\MeshRenderInfo.cpp" -o $(DirTemp)/MeshRenderInfo.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MeshStructure.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\MeshStructure.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\MeshStructure.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\MeshStructure.cpp" -o $(DirTemp)/MeshStructure.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Model.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\Model.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\Model.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\Model.cpp" -o $(DirTemp)/Model.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MTL.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\OBJ\MTL\MTL.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\OBJ\MTL\MTL.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\OBJ\MTL\MTL.cpp" -o $(DirTemp)/MTL.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/OBJ.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\OBJ\OBJ.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\OBJ\OBJ.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\OBJ\OBJ.cpp" -o $(DirTemp)/OBJ.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/OBJElement.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\OBJ\OBJElement.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\OBJ\OBJElement.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\OBJ\OBJElement.cpp" -o $(DirTemp)/OBJElement.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/PLY.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\PLY\PLY.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\PLY\PLY.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\PLY\PLY.cpp" -o $(DirTemp)/PLY.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/STL.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\STL\STL.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\STL\STL.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\STL\STL.cpp" -o $(DirTemp)/STL.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Vertex.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\Vertex.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\Vertex.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\Vertex.cpp" -o $(DirTemp)/Vertex.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/WRL.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\WRL\WRL.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\WRL\WRL.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Model\WRL\WRL.cpp" -o $(DirTemp)/WRL.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Client.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\Client.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\Client.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\Client.cpp" -o $(DirTemp)/Client.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IClientListener.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\IClientListener.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\IClientListener.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\IClientListener.hpp" -o $(DirTemp)/IClientListener.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IOSocket.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\IOSocket.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\IOSocket.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\IOSocket.cpp" -o $(DirTemp)/IOSocket.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IOSocketMessage.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\IOSocketMessage.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\IOSocketMessage.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\IOSocketMessage.cpp" -o $(DirTemp)/IOSocketMessage.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IPAdressFamily.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\IPAdressFamily.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\IPAdressFamily.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\IPAdressFamily.cpp" -o $(DirTemp)/IPAdressFamily.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IPAdressInfo.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\IPAdressInfo.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\IPAdressInfo.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\IPAdressInfo.cpp" -o $(DirTemp)/IPAdressInfo.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IPVersion.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\IPVersion.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\IPVersion.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\IPVersion.cpp" -o $(DirTemp)/IPVersion.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ProtocolMode.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\ProtocolMode.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\ProtocolMode.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\ProtocolMode.cpp" -o $(DirTemp)/ProtocolMode.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Server.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\Server.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\Server.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\Server.cpp" -o $(DirTemp)/Server.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ServerListeningThreadInfo.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\ServerListeningThreadInfo.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\ServerListeningThreadInfo.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\ServerListeningThreadInfo.cpp" -o $(DirTemp)/ServerListeningThreadInfo.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/SocketActionResult.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\SocketActionResult.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\SocketActionResult.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\SocketActionResult.cpp" -o $(DirTemp)/SocketActionResult.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/SocketType.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\SocketType.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\SocketType.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Network\SocketType.cpp" -o $(DirTemp)/SocketType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Resource.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Resource.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Resource.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Resource.cpp" -o $(DirTemp)/Resource.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ResourceType.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\ResourceType.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\ResourceType.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\ResourceType.hpp" -o $(DirTemp)/ResourceType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/HTTPError.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Service\HTTP\HTTPError.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Service\HTTP\HTTPError.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Service\HTTP\HTTPError.cpp" -o $(DirTemp)/HTTPError.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/HTTPRequestMethod.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Service\HTTP\HTTPRequestMethod.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Service\HTTP\HTTPRequestMethod.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Service\HTTP\HTTPRequestMethod.cpp" -o $(DirTemp)/HTTPRequestMethod.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/HTTPServer.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Service\HTTP\HTTPServer.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Service\HTTP\HTTPServer.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Service\HTTP\HTTPServer.cpp" -o $(DirTemp)/HTTPServer.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Shader.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Shader\Shader.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Shader\Shader.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Shader\Shader.cpp" -o $(DirTemp)/Shader.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ShaderProgram.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Shader\ShaderProgram.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Shader\ShaderProgram.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Shader\ShaderProgram.cpp" -o $(DirTemp)/ShaderProgram.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ShaderType.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Shader\ShaderType.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Shader\ShaderType.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Shader\ShaderType.cpp" -o $(DirTemp)/ShaderType.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/AAC.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\AAC\AAC.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\AAC\AAC.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\AAC\AAC.cpp" -o $(DirTemp)/AAC.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FLAC.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\FLAC\FLAC.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\FLAC\FLAC.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\FLAC\FLAC.cpp" -o $(DirTemp)/FLAC.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ISoundFormat.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\ISoundFormat.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\ISoundFormat.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\ISoundFormat.hpp" -o $(DirTemp)/ISoundFormat.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/M4A.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\M4A\M4A.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\M4A\M4A.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\M4A\M4A.cpp" -o $(DirTemp)/M4A.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MID.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MID\MID.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MID\MID.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MID\MID.cpp" -o $(DirTemp)/MID.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MIDICommand.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MID\MIDICommand.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MID\MIDICommand.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MID\MIDICommand.cpp" -o $(DirTemp)/MIDICommand.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MIDICommandExtended.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MID\MIDICommandExtended.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MID\MIDICommandExtended.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MID\MIDICommandExtended.cpp" -o $(DirTemp)/MIDICommandExtended.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MIDINote.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MID\MIDINote.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MID\MIDINote.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MID\MIDINote.cpp" -o $(DirTemp)/MIDINote.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MIDITrack.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MID\MIDITrack.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MID\MIDITrack.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MID\MIDITrack.cpp" -o $(DirTemp)/MIDITrack.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MIDITrackHeader.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MID\MIDITrackHeader.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MID\MIDITrackHeader.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MID\MIDITrackHeader.cpp" -o $(DirTemp)/MIDITrackHeader.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MP3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MP3.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MP3.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MP3.cpp" -o $(DirTemp)/MP3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MP3ChannelMode.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MP3ChannelMode.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MP3ChannelMode.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MP3ChannelMode.hpp" -o $(DirTemp)/MP3ChannelMode.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MP3Emphasis.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MP3Emphasis.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MP3Emphasis.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MP3Emphasis.hpp" -o $(DirTemp)/MP3Emphasis.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MP3Header.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MP3Header.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MP3Header.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MP3Header.cpp" -o $(DirTemp)/MP3Header.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MP3Layer.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MP3Layer.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MP3Layer.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MP3Layer.hpp" -o $(DirTemp)/MP3Layer.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MP3MPEGVersion.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MP3MPEGVersion.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MP3MPEGVersion.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MP3MPEGVersion.hpp" -o $(DirTemp)/MP3MPEGVersion.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MPEGAudioTag.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MPEGAudioTag.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MPEGAudioTag.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MPEGAudioTag.cpp" -o $(DirTemp)/MPEGAudioTag.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MPEGGenre.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MPEGGenre.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MPEGGenre.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MPEGGenre.cpp" -o $(DirTemp)/MPEGGenre.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MPEGGenre.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MPEGGenre.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MPEGGenre.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\MP3\MPEGGenre.hpp" -o $(DirTemp)/MPEGGenre.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/OGG.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\OGG\OGG.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\OGG\OGG.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\OGG\OGG.cpp" -o $(DirTemp)/OGG.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Sound.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\Sound.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\Sound.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\Sound.cpp" -o $(DirTemp)/Sound.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/SoundPlayStyle.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\SoundPlayStyle.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\SoundPlayStyle.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\SoundPlayStyle.hpp" -o $(DirTemp)/SoundPlayStyle.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/FMT.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\WAV\FMT.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\WAV\FMT.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\WAV\FMT.cpp" -o $(DirTemp)/FMT.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/RIFF.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\WAV\RIFF.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\WAV\RIFF.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\WAV\RIFF.cpp" -o $(DirTemp)/RIFF.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/WAV.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\WAV\WAV.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\WAV\WAV.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\WAV\WAV.cpp" -o $(DirTemp)/WAV.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/WMA.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\WMA\WMA.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\WMA\WMA.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Sound\WMA\WMA.cpp" -o $(DirTemp)/WMA.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/StopWatch.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Time\StopWatch.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Time\StopWatch.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Time\StopWatch.cpp" -o $(DirTemp)/StopWatch.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/UUID.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Types\UUID.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Types\UUID.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Types\UUID.cpp" -o $(DirTemp)/UUID.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/AVI.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Video\AVI\AVI.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Video\AVI\AVI.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Video\AVI\AVI.cpp" -o $(DirTemp)/AVI.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/AVIHeader.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Video\AVI\AVIHeader.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Video\AVI\AVIHeader.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Video\AVI\AVIHeader.cpp" -o $(DirTemp)/AVIHeader.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/IVideoFormat.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Video\IVideoFormat.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Video\IVideoFormat.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Video\IVideoFormat.hpp" -o $(DirTemp)/IVideoFormat.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/MP4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Video\MP4\MP4.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Video\MP4\MP4.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Video\MP4\MP4.cpp" -o $(DirTemp)/MP4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/Video.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Video\Video.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Video\Video.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemResource\Source\Video\Video.cpp" -o $(DirTemp)/Video.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/AudioConfig.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemSound\Source\AudioConfig.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemSound\Source\AudioConfig.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemSound\Source\AudioConfig.cpp" -o $(DirTemp)/AudioConfig.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/AudioSource.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemSound\Source\AudioSource.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemSound\Source\AudioSource.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemSound\Source\AudioSource.cpp" -o $(DirTemp)/AudioSource.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/SystemSound.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemSound\Source\SystemSound.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemSound\Source\SystemSound.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\SystemSound\Source\SystemSound.cpp" -o $(DirTemp)/SystemSound.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/main.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\TestNetwork\main.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\TestNetwork\main.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\TestNetwork\main.cpp" -o $(DirTemp)/main.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TestQuadTree.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\TestQuadTree\TestQuadTree.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\TestQuadTree\TestQuadTree.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\TestQuadTree\TestQuadTree.cpp" -o $(DirTemp)/TestQuadTree.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/pch.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\TestSystemResource\pch.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\TestSystemResource\pch.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\TestSystemResource\pch.cpp" -o $(DirTemp)/pch.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/TestSystemResource.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\TestSystemResource\TestSystemResource.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\TestSystemResource\TestSystemResource.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\TestSystemResource\TestSystemResource.cpp" -o $(DirTemp)/TestSystemResource.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/common.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\common.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\common.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\common.hpp" -o $(DirTemp)/common.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/compute_common.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\compute_common.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\compute_common.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\compute_common.hpp" -o $(DirTemp)/compute_common.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/compute_vector_relational.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\compute_vector_relational.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\compute_vector_relational.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\compute_vector_relational.hpp" -o $(DirTemp)/compute_vector_relational.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/glm.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\glm.cpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\glm.cpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\glm.cpp" -o $(DirTemp)/glm.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/qualifier.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\qualifier.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\qualifier.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\qualifier.hpp" -o $(DirTemp)/qualifier.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/setup.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\setup.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\setup.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\setup.hpp" -o $(DirTemp)/setup.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_float.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_float.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_float.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_float.hpp" -o $(DirTemp)/type_float.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_half.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_half.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_half.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_half.hpp" -o $(DirTemp)/type_half.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_mat2x2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat2x2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat2x2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat2x2.hpp" -o $(DirTemp)/type_mat2x2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_mat2x3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat2x3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat2x3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat2x3.hpp" -o $(DirTemp)/type_mat2x3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_mat2x4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat2x4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat2x4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat2x4.hpp" -o $(DirTemp)/type_mat2x4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_mat3x2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat3x2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat3x2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat3x2.hpp" -o $(DirTemp)/type_mat3x2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_mat3x3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat3x3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat3x3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat3x3.hpp" -o $(DirTemp)/type_mat3x3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_mat3x4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat3x4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat3x4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat3x4.hpp" -o $(DirTemp)/type_mat3x4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_mat4x2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat4x2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat4x2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat4x2.hpp" -o $(DirTemp)/type_mat4x2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_mat4x3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat4x3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat4x3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat4x3.hpp" -o $(DirTemp)/type_mat4x3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_mat4x4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat4x4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat4x4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_mat4x4.hpp" -o $(DirTemp)/type_mat4x4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_quat.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_quat.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_quat.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_quat.hpp" -o $(DirTemp)/type_quat.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_vec1.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_vec1.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_vec1.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_vec1.hpp" -o $(DirTemp)/type_vec1.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_vec2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_vec2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_vec2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_vec2.hpp" -o $(DirTemp)/type_vec2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_vec3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_vec3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_vec3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_vec3.hpp" -o $(DirTemp)/type_vec3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_vec4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_vec4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_vec4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\type_vec4.hpp" -o $(DirTemp)/type_vec4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/_features.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\_features.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\_features.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\_features.hpp" -o $(DirTemp)/_features.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/_fixes.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\_fixes.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\_fixes.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\_fixes.hpp" -o $(DirTemp)/_fixes.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/_noise.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\_noise.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\_noise.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\_noise.hpp" -o $(DirTemp)/_noise.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/_swizzle.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\_swizzle.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\_swizzle.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\_swizzle.hpp" -o $(DirTemp)/_swizzle.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/_swizzle_func.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\_swizzle_func.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\_swizzle_func.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\_swizzle_func.hpp" -o $(DirTemp)/_swizzle_func.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/_vectorize.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\_vectorize.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\_vectorize.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\detail\_vectorize.hpp" -o $(DirTemp)/_vectorize.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/exponential.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\exponential.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\exponential.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\exponential.hpp" -o $(DirTemp)/exponential.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_clip_space.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_clip_space.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_clip_space.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_clip_space.hpp" -o $(DirTemp)/matrix_clip_space.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_common.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_common.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_common.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_common.hpp" -o $(DirTemp)/matrix_common.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_double2x2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double2x2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double2x2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double2x2.hpp" -o $(DirTemp)/matrix_double2x2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_double2x2_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double2x2_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double2x2_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double2x2_precision.hpp" -o $(DirTemp)/matrix_double2x2_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_double2x3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double2x3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double2x3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double2x3.hpp" -o $(DirTemp)/matrix_double2x3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_double2x3_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double2x3_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double2x3_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double2x3_precision.hpp" -o $(DirTemp)/matrix_double2x3_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_double2x4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double2x4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double2x4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double2x4.hpp" -o $(DirTemp)/matrix_double2x4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_double2x4_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double2x4_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double2x4_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double2x4_precision.hpp" -o $(DirTemp)/matrix_double2x4_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_double3x2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double3x2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double3x2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double3x2.hpp" -o $(DirTemp)/matrix_double3x2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_double3x2_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double3x2_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double3x2_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double3x2_precision.hpp" -o $(DirTemp)/matrix_double3x2_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_double3x3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double3x3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double3x3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double3x3.hpp" -o $(DirTemp)/matrix_double3x3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_double3x3_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double3x3_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double3x3_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double3x3_precision.hpp" -o $(DirTemp)/matrix_double3x3_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_double3x4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double3x4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double3x4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double3x4.hpp" -o $(DirTemp)/matrix_double3x4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_double3x4_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double3x4_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double3x4_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double3x4_precision.hpp" -o $(DirTemp)/matrix_double3x4_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_double4x2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double4x2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double4x2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double4x2.hpp" -o $(DirTemp)/matrix_double4x2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_double4x2_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double4x2_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double4x2_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double4x2_precision.hpp" -o $(DirTemp)/matrix_double4x2_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_double4x3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double4x3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double4x3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double4x3.hpp" -o $(DirTemp)/matrix_double4x3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_double4x3_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double4x3_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double4x3_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double4x3_precision.hpp" -o $(DirTemp)/matrix_double4x3_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_double4x4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double4x4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double4x4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double4x4.hpp" -o $(DirTemp)/matrix_double4x4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_double4x4_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double4x4_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double4x4_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_double4x4_precision.hpp" -o $(DirTemp)/matrix_double4x4_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_float2x2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float2x2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float2x2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float2x2.hpp" -o $(DirTemp)/matrix_float2x2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_float2x2_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float2x2_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float2x2_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float2x2_precision.hpp" -o $(DirTemp)/matrix_float2x2_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_float2x3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float2x3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float2x3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float2x3.hpp" -o $(DirTemp)/matrix_float2x3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_float2x3_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float2x3_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float2x3_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float2x3_precision.hpp" -o $(DirTemp)/matrix_float2x3_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_float2x4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float2x4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float2x4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float2x4.hpp" -o $(DirTemp)/matrix_float2x4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_float2x4_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float2x4_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float2x4_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float2x4_precision.hpp" -o $(DirTemp)/matrix_float2x4_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_float3x2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float3x2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float3x2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float3x2.hpp" -o $(DirTemp)/matrix_float3x2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_float3x2_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float3x2_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float3x2_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float3x2_precision.hpp" -o $(DirTemp)/matrix_float3x2_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_float3x3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float3x3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float3x3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float3x3.hpp" -o $(DirTemp)/matrix_float3x3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_float3x3_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float3x3_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float3x3_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float3x3_precision.hpp" -o $(DirTemp)/matrix_float3x3_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_float3x4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float3x4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float3x4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float3x4.hpp" -o $(DirTemp)/matrix_float3x4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_float3x4_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float3x4_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float3x4_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float3x4_precision.hpp" -o $(DirTemp)/matrix_float3x4_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_float4x2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float4x2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float4x2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float4x2.hpp" -o $(DirTemp)/matrix_float4x2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_float4x2_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float4x2_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float4x2_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float4x2_precision.hpp" -o $(DirTemp)/matrix_float4x2_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_float4x3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float4x3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float4x3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float4x3.hpp" -o $(DirTemp)/matrix_float4x3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_float4x3_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float4x3_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float4x3_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float4x3_precision.hpp" -o $(DirTemp)/matrix_float4x3_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_float4x4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float4x4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float4x4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float4x4.hpp" -o $(DirTemp)/matrix_float4x4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_float4x4_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float4x4_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float4x4_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_float4x4_precision.hpp" -o $(DirTemp)/matrix_float4x4_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_int2x2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int2x2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int2x2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int2x2.hpp" -o $(DirTemp)/matrix_int2x2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_int2x2_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int2x2_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int2x2_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int2x2_sized.hpp" -o $(DirTemp)/matrix_int2x2_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_int2x3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int2x3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int2x3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int2x3.hpp" -o $(DirTemp)/matrix_int2x3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_int2x3_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int2x3_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int2x3_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int2x3_sized.hpp" -o $(DirTemp)/matrix_int2x3_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_int2x4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int2x4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int2x4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int2x4.hpp" -o $(DirTemp)/matrix_int2x4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_int2x4_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int2x4_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int2x4_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int2x4_sized.hpp" -o $(DirTemp)/matrix_int2x4_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_int3x2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int3x2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int3x2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int3x2.hpp" -o $(DirTemp)/matrix_int3x2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_int3x2_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int3x2_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int3x2_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int3x2_sized.hpp" -o $(DirTemp)/matrix_int3x2_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_int3x3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int3x3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int3x3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int3x3.hpp" -o $(DirTemp)/matrix_int3x3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_int3x3_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int3x3_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int3x3_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int3x3_sized.hpp" -o $(DirTemp)/matrix_int3x3_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_int3x4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int3x4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int3x4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int3x4.hpp" -o $(DirTemp)/matrix_int3x4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_int3x4_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int3x4_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int3x4_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int3x4_sized.hpp" -o $(DirTemp)/matrix_int3x4_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_int4x2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int4x2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int4x2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int4x2.hpp" -o $(DirTemp)/matrix_int4x2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_int4x2_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int4x2_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int4x2_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int4x2_sized.hpp" -o $(DirTemp)/matrix_int4x2_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_int4x3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int4x3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int4x3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int4x3.hpp" -o $(DirTemp)/matrix_int4x3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_int4x3_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int4x3_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int4x3_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int4x3_sized.hpp" -o $(DirTemp)/matrix_int4x3_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_int4x4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int4x4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int4x4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int4x4.hpp" -o $(DirTemp)/matrix_int4x4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_int4x4_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int4x4_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int4x4_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_int4x4_sized.hpp" -o $(DirTemp)/matrix_int4x4_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_projection.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_projection.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_projection.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_projection.hpp" -o $(DirTemp)/matrix_projection.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_relational.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_relational.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_relational.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_relational.hpp" -o $(DirTemp)/matrix_relational.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_transform.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_transform.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_transform.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_transform.hpp" -o $(DirTemp)/matrix_transform.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_uint2x2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint2x2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint2x2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint2x2.hpp" -o $(DirTemp)/matrix_uint2x2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_uint2x2_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint2x2_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint2x2_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint2x2_sized.hpp" -o $(DirTemp)/matrix_uint2x2_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_uint2x3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint2x3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint2x3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint2x3.hpp" -o $(DirTemp)/matrix_uint2x3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_uint2x3_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint2x3_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint2x3_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint2x3_sized.hpp" -o $(DirTemp)/matrix_uint2x3_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_uint2x4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint2x4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint2x4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint2x4.hpp" -o $(DirTemp)/matrix_uint2x4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_uint2x4_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint2x4_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint2x4_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint2x4_sized.hpp" -o $(DirTemp)/matrix_uint2x4_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_uint3x2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint3x2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint3x2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint3x2.hpp" -o $(DirTemp)/matrix_uint3x2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_uint3x2_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint3x2_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint3x2_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint3x2_sized.hpp" -o $(DirTemp)/matrix_uint3x2_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_uint3x3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint3x3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint3x3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint3x3.hpp" -o $(DirTemp)/matrix_uint3x3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_uint3x3_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint3x3_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint3x3_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint3x3_sized.hpp" -o $(DirTemp)/matrix_uint3x3_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_uint3x4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint3x4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint3x4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint3x4.hpp" -o $(DirTemp)/matrix_uint3x4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_uint3x4_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint3x4_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint3x4_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint3x4_sized.hpp" -o $(DirTemp)/matrix_uint3x4_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_uint4x2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint4x2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint4x2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint4x2.hpp" -o $(DirTemp)/matrix_uint4x2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_uint4x2_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint4x2_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint4x2_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint4x2_sized.hpp" -o $(DirTemp)/matrix_uint4x2_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_uint4x3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint4x3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint4x3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint4x3.hpp" -o $(DirTemp)/matrix_uint4x3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_uint4x3_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint4x3_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint4x3_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint4x3_sized.hpp" -o $(DirTemp)/matrix_uint4x3_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_uint4x4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint4x4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint4x4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint4x4.hpp" -o $(DirTemp)/matrix_uint4x4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_uint4x4_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint4x4_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint4x4_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\matrix_uint4x4_sized.hpp" -o $(DirTemp)/matrix_uint4x4_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/quaternion_common.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_common.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_common.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_common.hpp" -o $(DirTemp)/quaternion_common.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/quaternion_double.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_double.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_double.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_double.hpp" -o $(DirTemp)/quaternion_double.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/quaternion_double_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_double_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_double_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_double_precision.hpp" -o $(DirTemp)/quaternion_double_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/quaternion_exponential.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_exponential.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_exponential.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_exponential.hpp" -o $(DirTemp)/quaternion_exponential.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/quaternion_float.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_float.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_float.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_float.hpp" -o $(DirTemp)/quaternion_float.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/quaternion_float_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_float_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_float_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_float_precision.hpp" -o $(DirTemp)/quaternion_float_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/quaternion_geometric.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_geometric.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_geometric.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_geometric.hpp" -o $(DirTemp)/quaternion_geometric.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/quaternion_relational.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_relational.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_relational.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_relational.hpp" -o $(DirTemp)/quaternion_relational.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/quaternion_transform.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_transform.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_transform.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_transform.hpp" -o $(DirTemp)/quaternion_transform.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/quaternion_trigonometric.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_trigonometric.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_trigonometric.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\quaternion_trigonometric.hpp" -o $(DirTemp)/quaternion_trigonometric.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/scalar_common.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_common.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_common.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_common.hpp" -o $(DirTemp)/scalar_common.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/scalar_constants.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_constants.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_constants.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_constants.hpp" -o $(DirTemp)/scalar_constants.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/scalar_integer.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_integer.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_integer.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_integer.hpp" -o $(DirTemp)/scalar_integer.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/scalar_int_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_int_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_int_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_int_sized.hpp" -o $(DirTemp)/scalar_int_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/scalar_packing.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_packing.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_packing.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_packing.hpp" -o $(DirTemp)/scalar_packing.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/scalar_relational.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_relational.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_relational.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_relational.hpp" -o $(DirTemp)/scalar_relational.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/scalar_uint_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_uint_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_uint_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_uint_sized.hpp" -o $(DirTemp)/scalar_uint_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/scalar_ulp.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_ulp.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_ulp.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\scalar_ulp.hpp" -o $(DirTemp)/scalar_ulp.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_bool1.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool1.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool1.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool1.hpp" -o $(DirTemp)/vector_bool1.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_bool1_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool1_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool1_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool1_precision.hpp" -o $(DirTemp)/vector_bool1_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_bool2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool2.hpp" -o $(DirTemp)/vector_bool2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_bool2_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool2_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool2_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool2_precision.hpp" -o $(DirTemp)/vector_bool2_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_bool3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool3.hpp" -o $(DirTemp)/vector_bool3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_bool3_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool3_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool3_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool3_precision.hpp" -o $(DirTemp)/vector_bool3_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_bool4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool4.hpp" -o $(DirTemp)/vector_bool4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_bool4_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool4_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool4_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_bool4_precision.hpp" -o $(DirTemp)/vector_bool4_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_common.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_common.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_common.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_common.hpp" -o $(DirTemp)/vector_common.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_double1.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double1.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double1.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double1.hpp" -o $(DirTemp)/vector_double1.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_double1_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double1_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double1_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double1_precision.hpp" -o $(DirTemp)/vector_double1_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_double2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double2.hpp" -o $(DirTemp)/vector_double2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_double2_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double2_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double2_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double2_precision.hpp" -o $(DirTemp)/vector_double2_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_double3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double3.hpp" -o $(DirTemp)/vector_double3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_double3_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double3_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double3_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double3_precision.hpp" -o $(DirTemp)/vector_double3_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_double4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double4.hpp" -o $(DirTemp)/vector_double4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_double4_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double4_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double4_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_double4_precision.hpp" -o $(DirTemp)/vector_double4_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_float1.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float1.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float1.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float1.hpp" -o $(DirTemp)/vector_float1.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_float1_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float1_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float1_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float1_precision.hpp" -o $(DirTemp)/vector_float1_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_float2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float2.hpp" -o $(DirTemp)/vector_float2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_float2_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float2_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float2_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float2_precision.hpp" -o $(DirTemp)/vector_float2_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_float3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float3.hpp" -o $(DirTemp)/vector_float3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_float3_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float3_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float3_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float3_precision.hpp" -o $(DirTemp)/vector_float3_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_float4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float4.hpp" -o $(DirTemp)/vector_float4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_float4_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float4_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float4_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_float4_precision.hpp" -o $(DirTemp)/vector_float4_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_int1.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int1.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int1.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int1.hpp" -o $(DirTemp)/vector_int1.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_int1_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int1_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int1_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int1_sized.hpp" -o $(DirTemp)/vector_int1_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_int2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int2.hpp" -o $(DirTemp)/vector_int2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_int2_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int2_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int2_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int2_sized.hpp" -o $(DirTemp)/vector_int2_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_int3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int3.hpp" -o $(DirTemp)/vector_int3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_int3_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int3_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int3_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int3_sized.hpp" -o $(DirTemp)/vector_int3_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_int4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int4.hpp" -o $(DirTemp)/vector_int4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_int4_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int4_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int4_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_int4_sized.hpp" -o $(DirTemp)/vector_int4_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_integer.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_integer.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_integer.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_integer.hpp" -o $(DirTemp)/vector_integer.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_packing.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_packing.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_packing.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_packing.hpp" -o $(DirTemp)/vector_packing.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_relational.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_relational.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_relational.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_relational.hpp" -o $(DirTemp)/vector_relational.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_uint1.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint1.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint1.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint1.hpp" -o $(DirTemp)/vector_uint1.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_uint1_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint1_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint1_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint1_sized.hpp" -o $(DirTemp)/vector_uint1_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_uint2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint2.hpp" -o $(DirTemp)/vector_uint2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_uint2_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint2_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint2_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint2_sized.hpp" -o $(DirTemp)/vector_uint2_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_uint3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint3.hpp" -o $(DirTemp)/vector_uint3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_uint3_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint3_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint3_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint3_sized.hpp" -o $(DirTemp)/vector_uint3_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_uint4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint4.hpp" -o $(DirTemp)/vector_uint4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_uint4_sized.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint4_sized.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint4_sized.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_uint4_sized.hpp" -o $(DirTemp)/vector_uint4_sized.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_ulp.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_ulp.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_ulp.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext\vector_ulp.hpp" -o $(DirTemp)/vector_ulp.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ext.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\ext.hpp" -o $(DirTemp)/ext.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/fwd.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\fwd.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\fwd.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\fwd.hpp" -o $(DirTemp)/fwd.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/geometric.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\geometric.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\geometric.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\geometric.hpp" -o $(DirTemp)/geometric.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/glm.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\glm.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\glm.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\glm.hpp" -o $(DirTemp)/glm.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/bitfield.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\bitfield.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\bitfield.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\bitfield.hpp" -o $(DirTemp)/bitfield.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/color_space.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\color_space.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\color_space.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\color_space.hpp" -o $(DirTemp)/color_space.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/constants.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\constants.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\constants.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\constants.hpp" -o $(DirTemp)/constants.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/epsilon.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\epsilon.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\epsilon.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\epsilon.hpp" -o $(DirTemp)/epsilon.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/integer.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\integer.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\integer.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\integer.hpp" -o $(DirTemp)/integer.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_access.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\matrix_access.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\matrix_access.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\matrix_access.hpp" -o $(DirTemp)/matrix_access.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_integer.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\matrix_integer.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\matrix_integer.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\matrix_integer.hpp" -o $(DirTemp)/matrix_integer.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_inverse.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\matrix_inverse.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\matrix_inverse.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\matrix_inverse.hpp" -o $(DirTemp)/matrix_inverse.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_transform.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\matrix_transform.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\matrix_transform.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\matrix_transform.hpp" -o $(DirTemp)/matrix_transform.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/noise.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\noise.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\noise.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\noise.hpp" -o $(DirTemp)/noise.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/packing.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\packing.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\packing.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\packing.hpp" -o $(DirTemp)/packing.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/quaternion.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\quaternion.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\quaternion.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\quaternion.hpp" -o $(DirTemp)/quaternion.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/random.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\random.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\random.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\random.hpp" -o $(DirTemp)/random.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/reciprocal.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\reciprocal.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\reciprocal.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\reciprocal.hpp" -o $(DirTemp)/reciprocal.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/round.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\round.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\round.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\round.hpp" -o $(DirTemp)/round.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_aligned.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\type_aligned.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\type_aligned.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\type_aligned.hpp" -o $(DirTemp)/type_aligned.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\type_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\type_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\type_precision.hpp" -o $(DirTemp)/type_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_ptr.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\type_ptr.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\type_ptr.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\type_ptr.hpp" -o $(DirTemp)/type_ptr.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/ulp.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\ulp.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\ulp.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\ulp.hpp" -o $(DirTemp)/ulp.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vec1.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\vec1.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\vec1.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtc\vec1.hpp" -o $(DirTemp)/vec1.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/associated_min_max.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\associated_min_max.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\associated_min_max.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\associated_min_max.hpp" -o $(DirTemp)/associated_min_max.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/bit.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\bit.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\bit.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\bit.hpp" -o $(DirTemp)/bit.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/closest_point.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\closest_point.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\closest_point.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\closest_point.hpp" -o $(DirTemp)/closest_point.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/color_encoding.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\color_encoding.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\color_encoding.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\color_encoding.hpp" -o $(DirTemp)/color_encoding.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/color_space.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\color_space.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\color_space.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\color_space.hpp" -o $(DirTemp)/color_space.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/color_space_YCoCg.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\color_space_YCoCg.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\color_space_YCoCg.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\color_space_YCoCg.hpp" -o $(DirTemp)/color_space_YCoCg.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/common.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\common.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\common.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\common.hpp" -o $(DirTemp)/common.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/compatibility.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\compatibility.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\compatibility.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\compatibility.hpp" -o $(DirTemp)/compatibility.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/component_wise.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\component_wise.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\component_wise.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\component_wise.hpp" -o $(DirTemp)/component_wise.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/dual_quaternion.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\dual_quaternion.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\dual_quaternion.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\dual_quaternion.hpp" -o $(DirTemp)/dual_quaternion.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/easing.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\easing.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\easing.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\easing.hpp" -o $(DirTemp)/easing.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/euler_angles.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\euler_angles.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\euler_angles.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\euler_angles.hpp" -o $(DirTemp)/euler_angles.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/extend.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\extend.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\extend.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\extend.hpp" -o $(DirTemp)/extend.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/extended_min_max.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\extended_min_max.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\extended_min_max.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\extended_min_max.hpp" -o $(DirTemp)/extended_min_max.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/exterior_product.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\exterior_product.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\exterior_product.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\exterior_product.hpp" -o $(DirTemp)/exterior_product.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/fast_exponential.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\fast_exponential.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\fast_exponential.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\fast_exponential.hpp" -o $(DirTemp)/fast_exponential.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/fast_square_root.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\fast_square_root.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\fast_square_root.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\fast_square_root.hpp" -o $(DirTemp)/fast_square_root.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/fast_trigonometry.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\fast_trigonometry.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\fast_trigonometry.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\fast_trigonometry.hpp" -o $(DirTemp)/fast_trigonometry.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/functions.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\functions.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\functions.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\functions.hpp" -o $(DirTemp)/functions.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/gradient_paint.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\gradient_paint.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\gradient_paint.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\gradient_paint.hpp" -o $(DirTemp)/gradient_paint.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/handed_coordinate_space.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\handed_coordinate_space.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\handed_coordinate_space.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\handed_coordinate_space.hpp" -o $(DirTemp)/handed_coordinate_space.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/hash.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\hash.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\hash.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\hash.hpp" -o $(DirTemp)/hash.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/integer.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\integer.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\integer.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\integer.hpp" -o $(DirTemp)/integer.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/intersect.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\intersect.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\intersect.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\intersect.hpp" -o $(DirTemp)/intersect.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/io.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\io.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\io.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\io.hpp" -o $(DirTemp)/io.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/log_base.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\log_base.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\log_base.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\log_base.hpp" -o $(DirTemp)/log_base.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_cross_product.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_cross_product.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_cross_product.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_cross_product.hpp" -o $(DirTemp)/matrix_cross_product.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_decompose.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_decompose.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_decompose.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_decompose.hpp" -o $(DirTemp)/matrix_decompose.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_factorisation.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_factorisation.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_factorisation.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_factorisation.hpp" -o $(DirTemp)/matrix_factorisation.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_interpolation.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_interpolation.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_interpolation.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_interpolation.hpp" -o $(DirTemp)/matrix_interpolation.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_major_storage.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_major_storage.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_major_storage.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_major_storage.hpp" -o $(DirTemp)/matrix_major_storage.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_operation.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_operation.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_operation.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_operation.hpp" -o $(DirTemp)/matrix_operation.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_query.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_query.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_query.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_query.hpp" -o $(DirTemp)/matrix_query.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix_transform_2d.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_transform_2d.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_transform_2d.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\matrix_transform_2d.hpp" -o $(DirTemp)/matrix_transform_2d.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/mixed_product.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\mixed_product.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\mixed_product.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\mixed_product.hpp" -o $(DirTemp)/mixed_product.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/norm.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\norm.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\norm.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\norm.hpp" -o $(DirTemp)/norm.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/normal.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\normal.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\normal.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\normal.hpp" -o $(DirTemp)/normal.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/normalize_dot.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\normalize_dot.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\normalize_dot.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\normalize_dot.hpp" -o $(DirTemp)/normalize_dot.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/number_precision.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\number_precision.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\number_precision.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\number_precision.hpp" -o $(DirTemp)/number_precision.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/optimum_pow.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\optimum_pow.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\optimum_pow.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\optimum_pow.hpp" -o $(DirTemp)/optimum_pow.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/orthonormalize.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\orthonormalize.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\orthonormalize.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\orthonormalize.hpp" -o $(DirTemp)/orthonormalize.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/perpendicular.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\perpendicular.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\perpendicular.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\perpendicular.hpp" -o $(DirTemp)/perpendicular.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/polar_coordinates.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\polar_coordinates.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\polar_coordinates.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\polar_coordinates.hpp" -o $(DirTemp)/polar_coordinates.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/projection.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\projection.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\projection.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\projection.hpp" -o $(DirTemp)/projection.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/quaternion.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\quaternion.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\quaternion.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\quaternion.hpp" -o $(DirTemp)/quaternion.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/range.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\range.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\range.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\range.hpp" -o $(DirTemp)/range.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/raw_data.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\raw_data.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\raw_data.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\raw_data.hpp" -o $(DirTemp)/raw_data.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/rotate_normalized_axis.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\rotate_normalized_axis.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\rotate_normalized_axis.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\rotate_normalized_axis.hpp" -o $(DirTemp)/rotate_normalized_axis.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/rotate_vector.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\rotate_vector.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\rotate_vector.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\rotate_vector.hpp" -o $(DirTemp)/rotate_vector.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/scalar_multiplication.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\scalar_multiplication.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\scalar_multiplication.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\scalar_multiplication.hpp" -o $(DirTemp)/scalar_multiplication.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/scalar_relational.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\scalar_relational.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\scalar_relational.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\scalar_relational.hpp" -o $(DirTemp)/scalar_relational.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/spline.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\spline.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\spline.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\spline.hpp" -o $(DirTemp)/spline.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/std_based_type.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\std_based_type.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\std_based_type.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\std_based_type.hpp" -o $(DirTemp)/std_based_type.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/string_cast.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\string_cast.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\string_cast.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\string_cast.hpp" -o $(DirTemp)/string_cast.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/texture.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\texture.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\texture.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\texture.hpp" -o $(DirTemp)/texture.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/transform.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\transform.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\transform.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\transform.hpp" -o $(DirTemp)/transform.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/transform2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\transform2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\transform2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\transform2.hpp" -o $(DirTemp)/transform2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_aligned.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\type_aligned.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\type_aligned.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\type_aligned.hpp" -o $(DirTemp)/type_aligned.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/type_trait.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\type_trait.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\type_trait.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\type_trait.hpp" -o $(DirTemp)/type_trait.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_angle.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\vector_angle.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\vector_angle.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\vector_angle.hpp" -o $(DirTemp)/vector_angle.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_query.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\vector_query.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\vector_query.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\vector_query.hpp" -o $(DirTemp)/vector_query.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vec_swizzle.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\vec_swizzle.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\vec_swizzle.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\vec_swizzle.hpp" -o $(DirTemp)/vec_swizzle.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/wrap.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\wrap.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\wrap.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\gtx\wrap.hpp" -o $(DirTemp)/wrap.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/integer.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\integer.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\integer.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\integer.hpp" -o $(DirTemp)/integer.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/mat2x2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat2x2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat2x2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat2x2.hpp" -o $(DirTemp)/mat2x2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/mat2x3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat2x3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat2x3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat2x3.hpp" -o $(DirTemp)/mat2x3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/mat2x4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat2x4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat2x4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat2x4.hpp" -o $(DirTemp)/mat2x4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/mat3x2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat3x2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat3x2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat3x2.hpp" -o $(DirTemp)/mat3x2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/mat3x3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat3x3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat3x3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat3x3.hpp" -o $(DirTemp)/mat3x3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/mat3x4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat3x4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat3x4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat3x4.hpp" -o $(DirTemp)/mat3x4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/mat4x2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat4x2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat4x2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat4x2.hpp" -o $(DirTemp)/mat4x2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/mat4x3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat4x3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat4x3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat4x3.hpp" -o $(DirTemp)/mat4x3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/mat4x4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat4x4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat4x4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\mat4x4.hpp" -o $(DirTemp)/mat4x4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/matrix.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\matrix.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\matrix.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\matrix.hpp" -o $(DirTemp)/matrix.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/packing.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\packing.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\packing.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\packing.hpp" -o $(DirTemp)/packing.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/trigonometric.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\trigonometric.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\trigonometric.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\trigonometric.hpp" -o $(DirTemp)/trigonometric.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vec2.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\vec2.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\vec2.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\vec2.hpp" -o $(DirTemp)/vec2.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vec3.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\vec3.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\vec3.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\vec3.hpp" -o $(DirTemp)/vec3.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vec4.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\vec4.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\vec4.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\vec4.hpp" -o $(DirTemp)/vec4.o
#-------------------------------------------------------------------------------------------------
$(DirTemp)/vector_relational.o: \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\vector_relational.hpp
	@echo "[#] Compiling file \_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\vector_relational.hpp"
	$(Compiler) -c "\_WorkSpace\Git\BitFireEngine_B\BitFireEngine\__Dependencies__\include\GLM\vector_relational.hpp" -o $(DirTemp)/vector_relational.o
#-------------------------------------------------------------------------------------------------
$(DirExport)/ExportLib: $(DirTemp)/SystemPhysics.o $(DirTemp)/Entity.o $(DirTemp)/Player.o $(DirTemp)/ResouceManager.o $(DirTemp)/BitFireEngine.o $(DirTemp)/IBitFireEngineListener.o $(DirTemp)/IBitFireEngineRenderListener.o $(DirTemp)/IBitFireEngineSoundListener.o $(DirTemp)/UIDialogBox.o $(DirTemp)/UIButton.o $(DirTemp)/UIElement.o $(DirTemp)/UIImage.o $(DirTemp)/UIText.o $(DirTemp)/BitFireEngineIDE.o $(DirTemp)/CleavedGameSystem.o $(DirTemp)/Main.o $(DirTemp)/Main.o $(DirTemp)/ZEEGameSystem.o $(DirTemp)/MakeFileGenerator.o $(DirTemp)/InputButton.o $(DirTemp)/InputContainer.o $(DirTemp)/InputSystem.o $(DirTemp)/KeyBoard.o $(DirTemp)/Mouse.o $(DirTemp)/OpenGLAPI.o $(DirTemp)/VideoConfig.o $(DirTemp)/VulcanAPI.o $(DirTemp)/Key.o $(DirTemp)/Window.o $(DirTemp)/Adler32.o $(DirTemp)/CRC32.o $(DirTemp)/ISBN.o $(DirTemp)/AsyncLock.o $(DirTemp)/Thread.o $(DirTemp)/Camera.o $(DirTemp)/CameraPerspective.o $(DirTemp)/ADAM7.o $(DirTemp)/DeflateBlock.o $(DirTemp)/DeflateEncodingMethod.o $(DirTemp)/HuffmanCodeType.o $(DirTemp)/HuffmanNumberCode.o $(DirTemp)/HuffmanSymbol.o $(DirTemp)/HuffmanTree.o $(DirTemp)/ZLIB.o $(DirTemp)/ZLIBCompressionLevel.o $(DirTemp)/ZLIBCompressionMethod.o $(DirTemp)/ZLIBHeader.o $(DirTemp)/AsciiString.o $(DirTemp)/BinaryTree.o $(DirTemp)/BinaryTreeData.o $(DirTemp)/BinaryTreeNode.o $(DirTemp)/BitStreamHusk.o $(DirTemp)/Dictionary.o $(DirTemp)/DictionaryStatic.o $(DirTemp)/LinkedList.o $(DirTemp)/LinkedListNode.o $(DirTemp)/List.o $(DirTemp)/QuadTree.o $(DirTemp)/QuadTreeDirection.o $(DirTemp)/QuadTreeNode.o $(DirTemp)/QuadTreePosition.o $(DirTemp)/Queue.o $(DirTemp)/RingBuffer.o $(DirTemp)/Table.o $(DirTemp)/Dialog.o $(DirTemp)/EML.o $(DirTemp)/Caesar.o $(DirTemp)/ICypher.o $(DirTemp)/RSA.o $(DirTemp)/ErrorCode.o $(DirTemp)/Event.o $(DirTemp)/Bash.o $(DirTemp)/ByteStream.o $(DirTemp)/File.o $(DirTemp)/FileActionResult.o $(DirTemp)/FileOpenMode.o $(DirTemp)/FilePersistence.o $(DirTemp)/FileStream.o $(DirTemp)/FileTemporary.o $(DirTemp)/IFIle.o $(DirTemp)/OpenFileDialog.o $(DirTemp)/Program.o $(DirTemp)/ProgramExecuteInfo.o $(DirTemp)/ProgramExecuteResultListener.o $(DirTemp)/FNT.o $(DirTemp)/FNTCharacter.o $(DirTemp)/FNTCommonData.o $(DirTemp)/FNTInfo.o $(DirTemp)/FNTPage.o $(DirTemp)/Font.o $(DirTemp)/IFontFormat.o $(DirTemp)/OTF.o $(DirTemp)/EncodingID.o $(DirTemp)/EncodingRecord.o $(DirTemp)/PlatformID.o $(DirTemp)/TTFCharacterMapping.o $(DirTemp)/TTFDigitalSignature.o $(DirTemp)/TTFDigitalSignatureBlock.o $(DirTemp)/TTFDigitalSignatureRecord.o $(DirTemp)/TTFKerning.o $(DirTemp)/TTFKerningPair.o $(DirTemp)/TTFKerningSubtable.o $(DirTemp)/TTFSubtableFormat0.o $(DirTemp)/TTFSubtableFormat2.o $(DirTemp)/TTFArmStyle.o $(DirTemp)/TTFContrast.o $(DirTemp)/TTFFamilyType.o $(DirTemp)/TTFHeightX.o $(DirTemp)/TTFLetterform.o $(DirTemp)/TTFMidline.o $(DirTemp)/TTFPanose.o $(DirTemp)/TTFProportion.o $(DirTemp)/TTFSerifStyle.o $(DirTemp)/TTFStrokeVariatoon.o $(DirTemp)/TTFWeight.o $(DirTemp)/TTFCompatibility.o $(DirTemp)/TTFHeader.o $(DirTemp)/TTFHorizontalHeader.o $(DirTemp)/TTFLinearThreshold.o $(DirTemp)/TTFMaximumProfile.o $(DirTemp)/TTFOffsetTable.o $(DirTemp)/TTFPostScript.o $(DirTemp)/TTFVersion.o $(DirTemp)/TTFVersionType.o $(DirTemp)/TTFVerticalDeviceMetrics.o $(DirTemp)/TTF.o $(DirTemp)/TTFTableEntry.o $(DirTemp)/TTFTableEntryType.o $(DirTemp)/SkyBox.o $(DirTemp)/Sprite.o $(DirTemp)/IFileFormat.o $(DirTemp)/BMP.o $(DirTemp)/BMPInfoHeader.o $(DirTemp)/BMPInfoHeaderType.o $(DirTemp)/BMPType.o $(DirTemp)/GIF.o $(DirTemp)/Image.o $(DirTemp)/ImageDataFormat.o $(DirTemp)/ImageType.o $(DirTemp)/JPEG.o $(DirTemp)/JPEGFileInfo.o $(DirTemp)/JPEGFrame.o $(DirTemp)/JPEGFrameComponent.o $(DirTemp)/JPEGHuffmanTable.o $(DirTemp)/JPEGMarker.o $(DirTemp)/JPEGScanSelector.o $(DirTemp)/JPEGScanStart.o $(DirTemp)/PNGBackgroundColor.o $(DirTemp)/PNGChunk.o $(DirTemp)/PNGChunkType.o $(DirTemp)/PNGColorType.o $(DirTemp)/PNGImageHeader.o $(DirTemp)/PNGInterlaceMethod.o $(DirTemp)/PNGLastModificationTime.o $(DirTemp)/PNGPalette.o $(DirTemp)/PNGPaletteHistogram.o $(DirTemp)/PNGPhysicalPixelDimension.o $(DirTemp)/PNGPrimaryChromatics.o $(DirTemp)/PNGSuggestedPalette.o $(DirTemp)/PNGTransparency.o $(DirTemp)/PNG.o $(DirTemp)/PNGColorCompressor.o $(DirTemp)/PNGColorTree.o $(DirTemp)/TGA.o $(DirTemp)/TGABitsPerPixel.o $(DirTemp)/TGAImageDataType.o $(DirTemp)/TIFF.o $(DirTemp)/Level.o $(DirTemp)/BoxPlot.o $(DirTemp)/AngleDegree.o $(DirTemp)/AngleRadians.o $(DirTemp)/Cone.o $(DirTemp)/Cube.o $(DirTemp)/Cuboid.o $(DirTemp)/Cylinder.o $(DirTemp)/Form.o $(DirTemp)/Icosahedron.o $(DirTemp)/Sphere.o $(DirTemp)/SquarePyramid.o $(DirTemp)/Matrix.o $(DirTemp)/Matrix2x2.o $(DirTemp)/Matrix3x3.o $(DirTemp)/Matrix4x4.o $(DirTemp)/Padding.o $(DirTemp)/Circle.o $(DirTemp)/Hexagon.o $(DirTemp)/Pentagon.o $(DirTemp)/Rectangle.o $(DirTemp)/Shape.o $(DirTemp)/Square.o $(DirTemp)/Star.o $(DirTemp)/Triangle.o $(DirTemp)/Vector2.o $(DirTemp)/Vector3.o $(DirTemp)/Vector4.o $(DirTemp)/Interpolate.o $(DirTemp)/Math.o $(DirTemp)/Collider.o $(DirTemp)/GravityCube.o $(DirTemp)/GravityField.o $(DirTemp)/GravitySphere.o $(DirTemp)/PhysicsDynamic.o $(DirTemp)/PhysicsStatic.o $(DirTemp)/A3DS.o $(DirTemp)/FBX.o $(DirTemp)/IModelFormat.o $(DirTemp)/LinkedMesh.o $(DirTemp)/Material.o $(DirTemp)/Mesh.o $(DirTemp)/MeshIndexData.o $(DirTemp)/MeshRenderInfo.o $(DirTemp)/MeshStructure.o $(DirTemp)/Model.o $(DirTemp)/MTL.o $(DirTemp)/OBJ.o $(DirTemp)/OBJElement.o $(DirTemp)/PLY.o $(DirTemp)/STL.o $(DirTemp)/Vertex.o $(DirTemp)/WRL.o $(DirTemp)/Client.o $(DirTemp)/IClientListener.o $(DirTemp)/IOSocket.o $(DirTemp)/IOSocketMessage.o $(DirTemp)/IPAdressFamily.o $(DirTemp)/IPAdressInfo.o $(DirTemp)/IPVersion.o $(DirTemp)/ProtocolMode.o $(DirTemp)/Server.o $(DirTemp)/ServerListeningThreadInfo.o $(DirTemp)/SocketActionResult.o $(DirTemp)/SocketType.o $(DirTemp)/Resource.o $(DirTemp)/ResourceType.o $(DirTemp)/HTTPError.o $(DirTemp)/HTTPRequestMethod.o $(DirTemp)/HTTPServer.o $(DirTemp)/Shader.o $(DirTemp)/ShaderProgram.o $(DirTemp)/ShaderType.o $(DirTemp)/AAC.o $(DirTemp)/FLAC.o $(DirTemp)/ISoundFormat.o $(DirTemp)/M4A.o $(DirTemp)/MID.o $(DirTemp)/MIDICommand.o $(DirTemp)/MIDICommandExtended.o $(DirTemp)/MIDINote.o $(DirTemp)/MIDITrack.o $(DirTemp)/MIDITrackHeader.o $(DirTemp)/MP3.o $(DirTemp)/MP3ChannelMode.o $(DirTemp)/MP3Emphasis.o $(DirTemp)/MP3Header.o $(DirTemp)/MP3Layer.o $(DirTemp)/MP3MPEGVersion.o $(DirTemp)/MPEGAudioTag.o $(DirTemp)/MPEGGenre.o $(DirTemp)/MPEGGenre.o $(DirTemp)/OGG.o $(DirTemp)/Sound.o $(DirTemp)/SoundPlayStyle.o $(DirTemp)/FMT.o $(DirTemp)/RIFF.o $(DirTemp)/WAV.o $(DirTemp)/WMA.o $(DirTemp)/StopWatch.o $(DirTemp)/UUID.o $(DirTemp)/AVI.o $(DirTemp)/AVIHeader.o $(DirTemp)/IVideoFormat.o $(DirTemp)/MP4.o $(DirTemp)/Video.o $(DirTemp)/AudioConfig.o $(DirTemp)/AudioSource.o $(DirTemp)/SystemSound.o $(DirTemp)/main.o $(DirTemp)/TestQuadTree.o $(DirTemp)/pch.o $(DirTemp)/TestSystemResource.o $(DirTemp)/common.o $(DirTemp)/compute_common.o $(DirTemp)/compute_vector_relational.o $(DirTemp)/glm.o $(DirTemp)/qualifier.o $(DirTemp)/setup.o $(DirTemp)/type_float.o $(DirTemp)/type_half.o $(DirTemp)/type_mat2x2.o $(DirTemp)/type_mat2x3.o $(DirTemp)/type_mat2x4.o $(DirTemp)/type_mat3x2.o $(DirTemp)/type_mat3x3.o $(DirTemp)/type_mat3x4.o $(DirTemp)/type_mat4x2.o $(DirTemp)/type_mat4x3.o $(DirTemp)/type_mat4x4.o $(DirTemp)/type_quat.o $(DirTemp)/type_vec1.o $(DirTemp)/type_vec2.o $(DirTemp)/type_vec3.o $(DirTemp)/type_vec4.o $(DirTemp)/_features.o $(DirTemp)/_fixes.o $(DirTemp)/_noise.o $(DirTemp)/_swizzle.o $(DirTemp)/_swizzle_func.o $(DirTemp)/_vectorize.o $(DirTemp)/exponential.o $(DirTemp)/matrix_clip_space.o $(DirTemp)/matrix_common.o $(DirTemp)/matrix_double2x2.o $(DirTemp)/matrix_double2x2_precision.o $(DirTemp)/matrix_double2x3.o $(DirTemp)/matrix_double2x3_precision.o $(DirTemp)/matrix_double2x4.o $(DirTemp)/matrix_double2x4_precision.o $(DirTemp)/matrix_double3x2.o $(DirTemp)/matrix_double3x2_precision.o $(DirTemp)/matrix_double3x3.o $(DirTemp)/matrix_double3x3_precision.o $(DirTemp)/matrix_double3x4.o $(DirTemp)/matrix_double3x4_precision.o $(DirTemp)/matrix_double4x2.o $(DirTemp)/matrix_double4x2_precision.o $(DirTemp)/matrix_double4x3.o $(DirTemp)/matrix_double4x3_precision.o $(DirTemp)/matrix_double4x4.o $(DirTemp)/matrix_double4x4_precision.o $(DirTemp)/matrix_float2x2.o $(DirTemp)/matrix_float2x2_precision.o $(DirTemp)/matrix_float2x3.o $(DirTemp)/matrix_float2x3_precision.o $(DirTemp)/matrix_float2x4.o $(DirTemp)/matrix_float2x4_precision.o $(DirTemp)/matrix_float3x2.o $(DirTemp)/matrix_float3x2_precision.o $(DirTemp)/matrix_float3x3.o $(DirTemp)/matrix_float3x3_precision.o $(DirTemp)/matrix_float3x4.o $(DirTemp)/matrix_float3x4_precision.o $(DirTemp)/matrix_float4x2.o $(DirTemp)/matrix_float4x2_precision.o $(DirTemp)/matrix_float4x3.o $(DirTemp)/matrix_float4x3_precision.o $(DirTemp)/matrix_float4x4.o $(DirTemp)/matrix_float4x4_precision.o $(DirTemp)/matrix_int2x2.o $(DirTemp)/matrix_int2x2_sized.o $(DirTemp)/matrix_int2x3.o $(DirTemp)/matrix_int2x3_sized.o $(DirTemp)/matrix_int2x4.o $(DirTemp)/matrix_int2x4_sized.o $(DirTemp)/matrix_int3x2.o $(DirTemp)/matrix_int3x2_sized.o $(DirTemp)/matrix_int3x3.o $(DirTemp)/matrix_int3x3_sized.o $(DirTemp)/matrix_int3x4.o $(DirTemp)/matrix_int3x4_sized.o $(DirTemp)/matrix_int4x2.o $(DirTemp)/matrix_int4x2_sized.o $(DirTemp)/matrix_int4x3.o $(DirTemp)/matrix_int4x3_sized.o $(DirTemp)/matrix_int4x4.o $(DirTemp)/matrix_int4x4_sized.o $(DirTemp)/matrix_projection.o $(DirTemp)/matrix_relational.o $(DirTemp)/matrix_transform.o $(DirTemp)/matrix_uint2x2.o $(DirTemp)/matrix_uint2x2_sized.o $(DirTemp)/matrix_uint2x3.o $(DirTemp)/matrix_uint2x3_sized.o $(DirTemp)/matrix_uint2x4.o $(DirTemp)/matrix_uint2x4_sized.o $(DirTemp)/matrix_uint3x2.o $(DirTemp)/matrix_uint3x2_sized.o $(DirTemp)/matrix_uint3x3.o $(DirTemp)/matrix_uint3x3_sized.o $(DirTemp)/matrix_uint3x4.o $(DirTemp)/matrix_uint3x4_sized.o $(DirTemp)/matrix_uint4x2.o $(DirTemp)/matrix_uint4x2_sized.o $(DirTemp)/matrix_uint4x3.o $(DirTemp)/matrix_uint4x3_sized.o $(DirTemp)/matrix_uint4x4.o $(DirTemp)/matrix_uint4x4_sized.o $(DirTemp)/quaternion_common.o $(DirTemp)/quaternion_double.o $(DirTemp)/quaternion_double_precision.o $(DirTemp)/quaternion_exponential.o $(DirTemp)/quaternion_float.o $(DirTemp)/quaternion_float_precision.o $(DirTemp)/quaternion_geometric.o $(DirTemp)/quaternion_relational.o $(DirTemp)/quaternion_transform.o $(DirTemp)/quaternion_trigonometric.o $(DirTemp)/scalar_common.o $(DirTemp)/scalar_constants.o $(DirTemp)/scalar_integer.o $(DirTemp)/scalar_int_sized.o $(DirTemp)/scalar_packing.o $(DirTemp)/scalar_relational.o $(DirTemp)/scalar_uint_sized.o $(DirTemp)/scalar_ulp.o $(DirTemp)/vector_bool1.o $(DirTemp)/vector_bool1_precision.o $(DirTemp)/vector_bool2.o $(DirTemp)/vector_bool2_precision.o $(DirTemp)/vector_bool3.o $(DirTemp)/vector_bool3_precision.o $(DirTemp)/vector_bool4.o $(DirTemp)/vector_bool4_precision.o $(DirTemp)/vector_common.o $(DirTemp)/vector_double1.o $(DirTemp)/vector_double1_precision.o $(DirTemp)/vector_double2.o $(DirTemp)/vector_double2_precision.o $(DirTemp)/vector_double3.o $(DirTemp)/vector_double3_precision.o $(DirTemp)/vector_double4.o $(DirTemp)/vector_double4_precision.o $(DirTemp)/vector_float1.o $(DirTemp)/vector_float1_precision.o $(DirTemp)/vector_float2.o $(DirTemp)/vector_float2_precision.o $(DirTemp)/vector_float3.o $(DirTemp)/vector_float3_precision.o $(DirTemp)/vector_float4.o $(DirTemp)/vector_float4_precision.o $(DirTemp)/vector_int1.o $(DirTemp)/vector_int1_sized.o $(DirTemp)/vector_int2.o $(DirTemp)/vector_int2_sized.o $(DirTemp)/vector_int3.o $(DirTemp)/vector_int3_sized.o $(DirTemp)/vector_int4.o $(DirTemp)/vector_int4_sized.o $(DirTemp)/vector_integer.o $(DirTemp)/vector_packing.o $(DirTemp)/vector_relational.o $(DirTemp)/vector_uint1.o $(DirTemp)/vector_uint1_sized.o $(DirTemp)/vector_uint2.o $(DirTemp)/vector_uint2_sized.o $(DirTemp)/vector_uint3.o $(DirTemp)/vector_uint3_sized.o $(DirTemp)/vector_uint4.o $(DirTemp)/vector_uint4_sized.o $(DirTemp)/vector_ulp.o $(DirTemp)/ext.o $(DirTemp)/fwd.o $(DirTemp)/geometric.o $(DirTemp)/glm.o $(DirTemp)/bitfield.o $(DirTemp)/color_space.o $(DirTemp)/constants.o $(DirTemp)/epsilon.o $(DirTemp)/integer.o $(DirTemp)/matrix_access.o $(DirTemp)/matrix_integer.o $(DirTemp)/matrix_inverse.o $(DirTemp)/matrix_transform.o $(DirTemp)/noise.o $(DirTemp)/packing.o $(DirTemp)/quaternion.o $(DirTemp)/random.o $(DirTemp)/reciprocal.o $(DirTemp)/round.o $(DirTemp)/type_aligned.o $(DirTemp)/type_precision.o $(DirTemp)/type_ptr.o $(DirTemp)/ulp.o $(DirTemp)/vec1.o $(DirTemp)/associated_min_max.o $(DirTemp)/bit.o $(DirTemp)/closest_point.o $(DirTemp)/color_encoding.o $(DirTemp)/color_space.o $(DirTemp)/color_space_YCoCg.o $(DirTemp)/common.o $(DirTemp)/compatibility.o $(DirTemp)/component_wise.o $(DirTemp)/dual_quaternion.o $(DirTemp)/easing.o $(DirTemp)/euler_angles.o $(DirTemp)/extend.o $(DirTemp)/extended_min_max.o $(DirTemp)/exterior_product.o $(DirTemp)/fast_exponential.o $(DirTemp)/fast_square_root.o $(DirTemp)/fast_trigonometry.o $(DirTemp)/functions.o $(DirTemp)/gradient_paint.o $(DirTemp)/handed_coordinate_space.o $(DirTemp)/hash.o $(DirTemp)/integer.o $(DirTemp)/intersect.o $(DirTemp)/io.o $(DirTemp)/log_base.o $(DirTemp)/matrix_cross_product.o $(DirTemp)/matrix_decompose.o $(DirTemp)/matrix_factorisation.o $(DirTemp)/matrix_interpolation.o $(DirTemp)/matrix_major_storage.o $(DirTemp)/matrix_operation.o $(DirTemp)/matrix_query.o $(DirTemp)/matrix_transform_2d.o $(DirTemp)/mixed_product.o $(DirTemp)/norm.o $(DirTemp)/normal.o $(DirTemp)/normalize_dot.o $(DirTemp)/number_precision.o $(DirTemp)/optimum_pow.o $(DirTemp)/orthonormalize.o $(DirTemp)/perpendicular.o $(DirTemp)/polar_coordinates.o $(DirTemp)/projection.o $(DirTemp)/quaternion.o $(DirTemp)/range.o $(DirTemp)/raw_data.o $(DirTemp)/rotate_normalized_axis.o $(DirTemp)/rotate_vector.o $(DirTemp)/scalar_multiplication.o $(DirTemp)/scalar_relational.o $(DirTemp)/spline.o $(DirTemp)/std_based_type.o $(DirTemp)/string_cast.o $(DirTemp)/texture.o $(DirTemp)/transform.o $(DirTemp)/transform2.o $(DirTemp)/type_aligned.o $(DirTemp)/type_trait.o $(DirTemp)/vector_angle.o $(DirTemp)/vector_query.o $(DirTemp)/vec_swizzle.o $(DirTemp)/wrap.o $(DirTemp)/integer.o $(DirTemp)/mat2x2.o $(DirTemp)/mat2x3.o $(DirTemp)/mat2x4.o $(DirTemp)/mat3x2.o $(DirTemp)/mat3x3.o $(DirTemp)/mat3x4.o $(DirTemp)/mat4x2.o $(DirTemp)/mat4x3.o $(DirTemp)/mat4x4.o $(DirTemp)/matrix.o $(DirTemp)/packing.o $(DirTemp)/trigonometric.o $(DirTemp)/vec2.o $(DirTemp)/vec3.o $(DirTemp)/vec4.o $(DirTemp)/vector_relational.o 
	ar rcs $(DirExport)/ExportLib.lib $(DirTemp)/SystemPhysics.o $(DirTemp)/Entity.o $(DirTemp)/Player.o $(DirTemp)/ResouceManager.o $(DirTemp)/BitFireEngine.o $(DirTemp)/IBitFireEngineListener.o $(DirTemp)/IBitFireEngineRenderListener.o $(DirTemp)/IBitFireEngineSoundListener.o $(DirTemp)/UIDialogBox.o $(DirTemp)/UIButton.o $(DirTemp)/UIElement.o $(DirTemp)/UIImage.o $(DirTemp)/UIText.o $(DirTemp)/BitFireEngineIDE.o $(DirTemp)/CleavedGameSystem.o $(DirTemp)/Main.o $(DirTemp)/Main.o $(DirTemp)/ZEEGameSystem.o $(DirTemp)/MakeFileGenerator.o $(DirTemp)/InputButton.o $(DirTemp)/InputContainer.o $(DirTemp)/InputSystem.o $(DirTemp)/KeyBoard.o $(DirTemp)/Mouse.o $(DirTemp)/OpenGLAPI.o $(DirTemp)/VideoConfig.o $(DirTemp)/VulcanAPI.o $(DirTemp)/Key.o $(DirTemp)/Window.o $(DirTemp)/Adler32.o $(DirTemp)/CRC32.o $(DirTemp)/ISBN.o $(DirTemp)/AsyncLock.o $(DirTemp)/Thread.o $(DirTemp)/Camera.o $(DirTemp)/CameraPerspective.o $(DirTemp)/ADAM7.o $(DirTemp)/DeflateBlock.o $(DirTemp)/DeflateEncodingMethod.o $(DirTemp)/HuffmanCodeType.o $(DirTemp)/HuffmanNumberCode.o $(DirTemp)/HuffmanSymbol.o $(DirTemp)/HuffmanTree.o $(DirTemp)/ZLIB.o $(DirTemp)/ZLIBCompressionLevel.o $(DirTemp)/ZLIBCompressionMethod.o $(DirTemp)/ZLIBHeader.o $(DirTemp)/AsciiString.o $(DirTemp)/BinaryTree.o $(DirTemp)/BinaryTreeData.o $(DirTemp)/BinaryTreeNode.o $(DirTemp)/BitStreamHusk.o $(DirTemp)/Dictionary.o $(DirTemp)/DictionaryStatic.o $(DirTemp)/LinkedList.o $(DirTemp)/LinkedListNode.o $(DirTemp)/List.o $(DirTemp)/QuadTree.o $(DirTemp)/QuadTreeDirection.o $(DirTemp)/QuadTreeNode.o $(DirTemp)/QuadTreePosition.o $(DirTemp)/Queue.o $(DirTemp)/RingBuffer.o $(DirTemp)/Table.o $(DirTemp)/Dialog.o $(DirTemp)/EML.o $(DirTemp)/Caesar.o $(DirTemp)/ICypher.o $(DirTemp)/RSA.o $(DirTemp)/ErrorCode.o $(DirTemp)/Event.o $(DirTemp)/Bash.o $(DirTemp)/ByteStream.o $(DirTemp)/File.o $(DirTemp)/FileActionResult.o $(DirTemp)/FileOpenMode.o $(DirTemp)/FilePersistence.o $(DirTemp)/FileStream.o $(DirTemp)/FileTemporary.o $(DirTemp)/IFIle.o $(DirTemp)/OpenFileDialog.o $(DirTemp)/Program.o $(DirTemp)/ProgramExecuteInfo.o $(DirTemp)/ProgramExecuteResultListener.o $(DirTemp)/FNT.o $(DirTemp)/FNTCharacter.o $(DirTemp)/FNTCommonData.o $(DirTemp)/FNTInfo.o $(DirTemp)/FNTPage.o $(DirTemp)/Font.o $(DirTemp)/IFontFormat.o $(DirTemp)/OTF.o $(DirTemp)/EncodingID.o $(DirTemp)/EncodingRecord.o $(DirTemp)/PlatformID.o $(DirTemp)/TTFCharacterMapping.o $(DirTemp)/TTFDigitalSignature.o $(DirTemp)/TTFDigitalSignatureBlock.o $(DirTemp)/TTFDigitalSignatureRecord.o $(DirTemp)/TTFKerning.o $(DirTemp)/TTFKerningPair.o $(DirTemp)/TTFKerningSubtable.o $(DirTemp)/TTFSubtableFormat0.o $(DirTemp)/TTFSubtableFormat2.o $(DirTemp)/TTFArmStyle.o $(DirTemp)/TTFContrast.o $(DirTemp)/TTFFamilyType.o $(DirTemp)/TTFHeightX.o $(DirTemp)/TTFLetterform.o $(DirTemp)/TTFMidline.o $(DirTemp)/TTFPanose.o $(DirTemp)/TTFProportion.o $(DirTemp)/TTFSerifStyle.o $(DirTemp)/TTFStrokeVariatoon.o $(DirTemp)/TTFWeight.o $(DirTemp)/TTFCompatibility.o $(DirTemp)/TTFHeader.o $(DirTemp)/TTFHorizontalHeader.o $(DirTemp)/TTFLinearThreshold.o $(DirTemp)/TTFMaximumProfile.o $(DirTemp)/TTFOffsetTable.o $(DirTemp)/TTFPostScript.o $(DirTemp)/TTFVersion.o $(DirTemp)/TTFVersionType.o $(DirTemp)/TTFVerticalDeviceMetrics.o $(DirTemp)/TTF.o $(DirTemp)/TTFTableEntry.o $(DirTemp)/TTFTableEntryType.o $(DirTemp)/SkyBox.o $(DirTemp)/Sprite.o $(DirTemp)/IFileFormat.o $(DirTemp)/BMP.o $(DirTemp)/BMPInfoHeader.o $(DirTemp)/BMPInfoHeaderType.o $(DirTemp)/BMPType.o $(DirTemp)/GIF.o $(DirTemp)/Image.o $(DirTemp)/ImageDataFormat.o $(DirTemp)/ImageType.o $(DirTemp)/JPEG.o $(DirTemp)/JPEGFileInfo.o $(DirTemp)/JPEGFrame.o $(DirTemp)/JPEGFrameComponent.o $(DirTemp)/JPEGHuffmanTable.o $(DirTemp)/JPEGMarker.o $(DirTemp)/JPEGScanSelector.o $(DirTemp)/JPEGScanStart.o $(DirTemp)/PNGBackgroundColor.o $(DirTemp)/PNGChunk.o $(DirTemp)/PNGChunkType.o $(DirTemp)/PNGColorType.o $(DirTemp)/PNGImageHeader.o $(DirTemp)/PNGInterlaceMethod.o $(DirTemp)/PNGLastModificationTime.o $(DirTemp)/PNGPalette.o $(DirTemp)/PNGPaletteHistogram.o $(DirTemp)/PNGPhysicalPixelDimension.o $(DirTemp)/PNGPrimaryChromatics.o $(DirTemp)/PNGSuggestedPalette.o $(DirTemp)/PNGTransparency.o $(DirTemp)/PNG.o $(DirTemp)/PNGColorCompressor.o $(DirTemp)/PNGColorTree.o $(DirTemp)/TGA.o $(DirTemp)/TGABitsPerPixel.o $(DirTemp)/TGAImageDataType.o $(DirTemp)/TIFF.o $(DirTemp)/Level.o $(DirTemp)/BoxPlot.o $(DirTemp)/AngleDegree.o $(DirTemp)/AngleRadians.o $(DirTemp)/Cone.o $(DirTemp)/Cube.o $(DirTemp)/Cuboid.o $(DirTemp)/Cylinder.o $(DirTemp)/Form.o $(DirTemp)/Icosahedron.o $(DirTemp)/Sphere.o $(DirTemp)/SquarePyramid.o $(DirTemp)/Matrix.o $(DirTemp)/Matrix2x2.o $(DirTemp)/Matrix3x3.o $(DirTemp)/Matrix4x4.o $(DirTemp)/Padding.o $(DirTemp)/Circle.o $(DirTemp)/Hexagon.o $(DirTemp)/Pentagon.o $(DirTemp)/Rectangle.o $(DirTemp)/Shape.o $(DirTemp)/Square.o $(DirTemp)/Star.o $(DirTemp)/Triangle.o $(DirTemp)/Vector2.o $(DirTemp)/Vector3.o $(DirTemp)/Vector4.o $(DirTemp)/Interpolate.o $(DirTemp)/Math.o $(DirTemp)/Collider.o $(DirTemp)/GravityCube.o $(DirTemp)/GravityField.o $(DirTemp)/GravitySphere.o $(DirTemp)/PhysicsDynamic.o $(DirTemp)/PhysicsStatic.o $(DirTemp)/A3DS.o $(DirTemp)/FBX.o $(DirTemp)/IModelFormat.o $(DirTemp)/LinkedMesh.o $(DirTemp)/Material.o $(DirTemp)/Mesh.o $(DirTemp)/MeshIndexData.o $(DirTemp)/MeshRenderInfo.o $(DirTemp)/MeshStructure.o $(DirTemp)/Model.o $(DirTemp)/MTL.o $(DirTemp)/OBJ.o $(DirTemp)/OBJElement.o $(DirTemp)/PLY.o $(DirTemp)/STL.o $(DirTemp)/Vertex.o $(DirTemp)/WRL.o $(DirTemp)/Client.o $(DirTemp)/IClientListener.o $(DirTemp)/IOSocket.o $(DirTemp)/IOSocketMessage.o $(DirTemp)/IPAdressFamily.o $(DirTemp)/IPAdressInfo.o $(DirTemp)/IPVersion.o $(DirTemp)/ProtocolMode.o $(DirTemp)/Server.o $(DirTemp)/ServerListeningThreadInfo.o $(DirTemp)/SocketActionResult.o $(DirTemp)/SocketType.o $(DirTemp)/Resource.o $(DirTemp)/ResourceType.o $(DirTemp)/HTTPError.o $(DirTemp)/HTTPRequestMethod.o $(DirTemp)/HTTPServer.o $(DirTemp)/Shader.o $(DirTemp)/ShaderProgram.o $(DirTemp)/ShaderType.o $(DirTemp)/AAC.o $(DirTemp)/FLAC.o $(DirTemp)/ISoundFormat.o $(DirTemp)/M4A.o $(DirTemp)/MID.o $(DirTemp)/MIDICommand.o $(DirTemp)/MIDICommandExtended.o $(DirTemp)/MIDINote.o $(DirTemp)/MIDITrack.o $(DirTemp)/MIDITrackHeader.o $(DirTemp)/MP3.o $(DirTemp)/MP3ChannelMode.o $(DirTemp)/MP3Emphasis.o $(DirTemp)/MP3Header.o $(DirTemp)/MP3Layer.o $(DirTemp)/MP3MPEGVersion.o $(DirTemp)/MPEGAudioTag.o $(DirTemp)/MPEGGenre.o $(DirTemp)/MPEGGenre.o $(DirTemp)/OGG.o $(DirTemp)/Sound.o $(DirTemp)/SoundPlayStyle.o $(DirTemp)/FMT.o $(DirTemp)/RIFF.o $(DirTemp)/WAV.o $(DirTemp)/WMA.o $(DirTemp)/StopWatch.o $(DirTemp)/UUID.o $(DirTemp)/AVI.o $(DirTemp)/AVIHeader.o $(DirTemp)/IVideoFormat.o $(DirTemp)/MP4.o $(DirTemp)/Video.o $(DirTemp)/AudioConfig.o $(DirTemp)/AudioSource.o $(DirTemp)/SystemSound.o $(DirTemp)/main.o $(DirTemp)/TestQuadTree.o $(DirTemp)/pch.o $(DirTemp)/TestSystemResource.o $(DirTemp)/common.o $(DirTemp)/compute_common.o $(DirTemp)/compute_vector_relational.o $(DirTemp)/glm.o $(DirTemp)/qualifier.o $(DirTemp)/setup.o $(DirTemp)/type_float.o $(DirTemp)/type_half.o $(DirTemp)/type_mat2x2.o $(DirTemp)/type_mat2x3.o $(DirTemp)/type_mat2x4.o $(DirTemp)/type_mat3x2.o $(DirTemp)/type_mat3x3.o $(DirTemp)/type_mat3x4.o $(DirTemp)/type_mat4x2.o $(DirTemp)/type_mat4x3.o $(DirTemp)/type_mat4x4.o $(DirTemp)/type_quat.o $(DirTemp)/type_vec1.o $(DirTemp)/type_vec2.o $(DirTemp)/type_vec3.o $(DirTemp)/type_vec4.o $(DirTemp)/_features.o $(DirTemp)/_fixes.o $(DirTemp)/_noise.o $(DirTemp)/_swizzle.o $(DirTemp)/_swizzle_func.o $(DirTemp)/_vectorize.o $(DirTemp)/exponential.o $(DirTemp)/matrix_clip_space.o $(DirTemp)/matrix_common.o $(DirTemp)/matrix_double2x2.o $(DirTemp)/matrix_double2x2_precision.o $(DirTemp)/matrix_double2x3.o $(DirTemp)/matrix_double2x3_precision.o $(DirTemp)/matrix_double2x4.o $(DirTemp)/matrix_double2x4_precision.o $(DirTemp)/matrix_double3x2.o $(DirTemp)/matrix_double3x2_precision.o $(DirTemp)/matrix_double3x3.o $(DirTemp)/matrix_double3x3_precision.o $(DirTemp)/matrix_double3x4.o $(DirTemp)/matrix_double3x4_precision.o $(DirTemp)/matrix_double4x2.o $(DirTemp)/matrix_double4x2_precision.o $(DirTemp)/matrix_double4x3.o $(DirTemp)/matrix_double4x3_precision.o $(DirTemp)/matrix_double4x4.o $(DirTemp)/matrix_double4x4_precision.o $(DirTemp)/matrix_float2x2.o $(DirTemp)/matrix_float2x2_precision.o $(DirTemp)/matrix_float2x3.o $(DirTemp)/matrix_float2x3_precision.o $(DirTemp)/matrix_float2x4.o $(DirTemp)/matrix_float2x4_precision.o $(DirTemp)/matrix_float3x2.o $(DirTemp)/matrix_float3x2_precision.o $(DirTemp)/matrix_float3x3.o $(DirTemp)/matrix_float3x3_precision.o $(DirTemp)/matrix_float3x4.o $(DirTemp)/matrix_float3x4_precision.o $(DirTemp)/matrix_float4x2.o $(DirTemp)/matrix_float4x2_precision.o $(DirTemp)/matrix_float4x3.o $(DirTemp)/matrix_float4x3_precision.o $(DirTemp)/matrix_float4x4.o $(DirTemp)/matrix_float4x4_precision.o $(DirTemp)/matrix_int2x2.o $(DirTemp)/matrix_int2x2_sized.o $(DirTemp)/matrix_int2x3.o $(DirTemp)/matrix_int2x3_sized.o $(DirTemp)/matrix_int2x4.o $(DirTemp)/matrix_int2x4_sized.o $(DirTemp)/matrix_int3x2.o $(DirTemp)/matrix_int3x2_sized.o $(DirTemp)/matrix_int3x3.o $(DirTemp)/matrix_int3x3_sized.o $(DirTemp)/matrix_int3x4.o $(DirTemp)/matrix_int3x4_sized.o $(DirTemp)/matrix_int4x2.o $(DirTemp)/matrix_int4x2_sized.o $(DirTemp)/matrix_int4x3.o $(DirTemp)/matrix_int4x3_sized.o $(DirTemp)/matrix_int4x4.o $(DirTemp)/matrix_int4x4_sized.o $(DirTemp)/matrix_projection.o $(DirTemp)/matrix_relational.o $(DirTemp)/matrix_transform.o $(DirTemp)/matrix_uint2x2.o $(DirTemp)/matrix_uint2x2_sized.o $(DirTemp)/matrix_uint2x3.o $(DirTemp)/matrix_uint2x3_sized.o $(DirTemp)/matrix_uint2x4.o $(DirTemp)/matrix_uint2x4_sized.o $(DirTemp)/matrix_uint3x2.o $(DirTemp)/matrix_uint3x2_sized.o $(DirTemp)/matrix_uint3x3.o $(DirTemp)/matrix_uint3x3_sized.o $(DirTemp)/matrix_uint3x4.o $(DirTemp)/matrix_uint3x4_sized.o $(DirTemp)/matrix_uint4x2.o $(DirTemp)/matrix_uint4x2_sized.o $(DirTemp)/matrix_uint4x3.o $(DirTemp)/matrix_uint4x3_sized.o $(DirTemp)/matrix_uint4x4.o $(DirTemp)/matrix_uint4x4_sized.o $(DirTemp)/quaternion_common.o $(DirTemp)/quaternion_double.o $(DirTemp)/quaternion_double_precision.o $(DirTemp)/quaternion_exponential.o $(DirTemp)/quaternion_float.o $(DirTemp)/quaternion_float_precision.o $(DirTemp)/quaternion_geometric.o $(DirTemp)/quaternion_relational.o $(DirTemp)/quaternion_transform.o $(DirTemp)/quaternion_trigonometric.o $(DirTemp)/scalar_common.o $(DirTemp)/scalar_constants.o $(DirTemp)/scalar_integer.o $(DirTemp)/scalar_int_sized.o $(DirTemp)/scalar_packing.o $(DirTemp)/scalar_relational.o $(DirTemp)/scalar_uint_sized.o $(DirTemp)/scalar_ulp.o $(DirTemp)/vector_bool1.o $(DirTemp)/vector_bool1_precision.o $(DirTemp)/vector_bool2.o $(DirTemp)/vector_bool2_precision.o $(DirTemp)/vector_bool3.o $(DirTemp)/vector_bool3_precision.o $(DirTemp)/vector_bool4.o $(DirTemp)/vector_bool4_precision.o $(DirTemp)/vector_common.o $(DirTemp)/vector_double1.o $(DirTemp)/vector_double1_precision.o $(DirTemp)/vector_double2.o $(DirTemp)/vector_double2_precision.o $(DirTemp)/vector_double3.o $(DirTemp)/vector_double3_precision.o $(DirTemp)/vector_double4.o $(DirTemp)/vector_double4_precision.o $(DirTemp)/vector_float1.o $(DirTemp)/vector_float1_precision.o $(DirTemp)/vector_float2.o $(DirTemp)/vector_float2_precision.o $(DirTemp)/vector_float3.o $(DirTemp)/vector_float3_precision.o $(DirTemp)/vector_float4.o $(DirTemp)/vector_float4_precision.o $(DirTemp)/vector_int1.o $(DirTemp)/vector_int1_sized.o $(DirTemp)/vector_int2.o $(DirTemp)/vector_int2_sized.o $(DirTemp)/vector_int3.o $(DirTemp)/vector_int3_sized.o $(DirTemp)/vector_int4.o $(DirTemp)/vector_int4_sized.o $(DirTemp)/vector_integer.o $(DirTemp)/vector_packing.o $(DirTemp)/vector_relational.o $(DirTemp)/vector_uint1.o $(DirTemp)/vector_uint1_sized.o $(DirTemp)/vector_uint2.o $(DirTemp)/vector_uint2_sized.o $(DirTemp)/vector_uint3.o $(DirTemp)/vector_uint3_sized.o $(DirTemp)/vector_uint4.o $(DirTemp)/vector_uint4_sized.o $(DirTemp)/vector_ulp.o $(DirTemp)/ext.o $(DirTemp)/fwd.o $(DirTemp)/geometric.o $(DirTemp)/glm.o $(DirTemp)/bitfield.o $(DirTemp)/color_space.o $(DirTemp)/constants.o $(DirTemp)/epsilon.o $(DirTemp)/integer.o $(DirTemp)/matrix_access.o $(DirTemp)/matrix_integer.o $(DirTemp)/matrix_inverse.o $(DirTemp)/matrix_transform.o $(DirTemp)/noise.o $(DirTemp)/packing.o $(DirTemp)/quaternion.o $(DirTemp)/random.o $(DirTemp)/reciprocal.o $(DirTemp)/round.o $(DirTemp)/type_aligned.o $(DirTemp)/type_precision.o $(DirTemp)/type_ptr.o $(DirTemp)/ulp.o $(DirTemp)/vec1.o $(DirTemp)/associated_min_max.o $(DirTemp)/bit.o $(DirTemp)/closest_point.o $(DirTemp)/color_encoding.o $(DirTemp)/color_space.o $(DirTemp)/color_space_YCoCg.o $(DirTemp)/common.o $(DirTemp)/compatibility.o $(DirTemp)/component_wise.o $(DirTemp)/dual_quaternion.o $(DirTemp)/easing.o $(DirTemp)/euler_angles.o $(DirTemp)/extend.o $(DirTemp)/extended_min_max.o $(DirTemp)/exterior_product.o $(DirTemp)/fast_exponential.o $(DirTemp)/fast_square_root.o $(DirTemp)/fast_trigonometry.o $(DirTemp)/functions.o $(DirTemp)/gradient_paint.o $(DirTemp)/handed_coordinate_space.o $(DirTemp)/hash.o $(DirTemp)/integer.o $(DirTemp)/intersect.o $(DirTemp)/io.o $(DirTemp)/log_base.o $(DirTemp)/matrix_cross_product.o $(DirTemp)/matrix_decompose.o $(DirTemp)/matrix_factorisation.o $(DirTemp)/matrix_interpolation.o $(DirTemp)/matrix_major_storage.o $(DirTemp)/matrix_operation.o $(DirTemp)/matrix_query.o $(DirTemp)/matrix_transform_2d.o $(DirTemp)/mixed_product.o $(DirTemp)/norm.o $(DirTemp)/normal.o $(DirTemp)/normalize_dot.o $(DirTemp)/number_precision.o $(DirTemp)/optimum_pow.o $(DirTemp)/orthonormalize.o $(DirTemp)/perpendicular.o $(DirTemp)/polar_coordinates.o $(DirTemp)/projection.o $(DirTemp)/quaternion.o $(DirTemp)/range.o $(DirTemp)/raw_data.o $(DirTemp)/rotate_normalized_axis.o $(DirTemp)/rotate_vector.o $(DirTemp)/scalar_multiplication.o $(DirTemp)/scalar_relational.o $(DirTemp)/spline.o $(DirTemp)/std_based_type.o $(DirTemp)/string_cast.o $(DirTemp)/texture.o $(DirTemp)/transform.o $(DirTemp)/transform2.o $(DirTemp)/type_aligned.o $(DirTemp)/type_trait.o $(DirTemp)/vector_angle.o $(DirTemp)/vector_query.o $(DirTemp)/vec_swizzle.o $(DirTemp)/wrap.o $(DirTemp)/integer.o $(DirTemp)/mat2x2.o $(DirTemp)/mat2x3.o $(DirTemp)/mat2x4.o $(DirTemp)/mat3x2.o $(DirTemp)/mat3x3.o $(DirTemp)/mat3x4.o $(DirTemp)/mat4x2.o $(DirTemp)/mat4x3.o $(DirTemp)/mat4x4.o $(DirTemp)/matrix.o $(DirTemp)/packing.o $(DirTemp)/trigonometric.o $(DirTemp)/vec2.o $(DirTemp)/vec3.o $(DirTemp)/vec4.o $(DirTemp)/vector_relational.o 
#-------------------------------------------------------------------------------------------------
#########################################
