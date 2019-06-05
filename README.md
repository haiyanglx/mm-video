# mm-video
高通原生的编解码测试程序，代码设计方式值得借鉴


Precondition: 
a.device分别创建路径/sdcard/media_test/input/和/sdcard/media_test/output/路径 
b.创建的目录赋值777权限 

OMX TEST Steps: 
a. 分别将MasterConfg.xml和<input_xml>文件放入/sdcard/media_test/下面 
b. 将<input_file>数据放入/sdcard/media_test/input/ 
c. sdm660_64:/system/bin # ./mm-vidc-omx-test /sdcard/media_test /sdcard/media_test/<input_xml> 
d. /sdcard/media_test/output/<output_file>就是编码/解码生成的文件 


For example: 
(1)sdm660_64:/sdcard/media_test # cat MasterConfg.xml 
********************************************************* 

<xml> 
<InputFileRoot>/sdcard/media_test/input/</InputFileRoot> 
<OutputFileRoot>/sdcard/media_test/output/</OutputFileRoot> 
</xml> 
********************************************************* 

(2)sdm660_64:/sdcard/media_test # cat SampleDecodeTest_h265_1080P.xml 
********************************************************* 

<xml> 
<DecodeSession> 
<CompressionFormat>VIDEO_CodingHEVC</CompressionFormat> 
<OutputHeight>1080</OutputHeight> 
<OutputWidth>1920</OutputWidth> 
<InputFile>input_1920_1080.h265</InputFile> 
<TestCaseID>output_1920_1080.yuv</TestCaseID> 
<session_mode>dec</session_mode> 
</DecodeSession> 
</xml> 
********************************************************* 

(3) 
./mm-vidc-omx-test /sdcard/media_test /sdcard/media_test/SampleDecodeTest_h265_1080P.xml 
