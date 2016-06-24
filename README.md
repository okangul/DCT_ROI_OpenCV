# DCT_ROI_OpenCV


CS555/455                                                                                                            Fall 2015                                                               
CS555/455 Assignment 3
(Due on November 2, 2015 by 11:59pm)

Name: Okan Gul
E-Mail: ogul1@binghamton.edu

Purpose of the Project

	The purpose of the assignment 3 is to getting used to work with color domains and learning the basics of the HIS. For the first part we learn DCT compression and first work with 1d than implement the 2d one for our images. For the second part we make a region finding for not gray scale for RGB images to reaching our goal we work with HIS images and implement a algorithm for finding ROI`S.

Part A: Questions (27%)

(1) [9%] In the simple RGB image, the R, G and B component images have the intensity for each line as shown in the following diagram. What color would a person see in the middle column of this image?









Answer 1:

Red is 0.5 Green is 1 and Blue is 0.5 because of that the answer should like 128 255 128 so it should be pure Green with a boot in intensity due to additive gray component.

(2)	 [9%] The 8-bit images shown in Q6.16 (page-459) are (left to right) the H, S, and I component images. The numbers indicate gray-level values. Answer the following questions, explaining the basis for your answer in each. If it is not possible to answer a question based on the given information, explain the reason. 
           (a) Give the gray level values of all regions in the hue image.
(b) Give the gray level values of all regions in the saturation image.
(c) Give the gray level values of all regions in the intensity image.




Answer 2:

(a)	Give the gray level values of all regions in the hue image.

It is given that the colors in figure are primary spectrum colors. Also gray level images are 8-bit images. The latter condition says that hue values are only divided into maximum 256. Since hue values are in range of 0 to 360 this means hue values are now 360/255. It means that 0-360 hue values are compressed between 0-255. So for example yellow 60 is now 43 similarly green 120 is now85 in the image. The other two regions are simply should be 170 and 213. At last the region in the middle is white so its hue value should be 0.

(b)	Give the gray level values of all regions in the saturation image.

Colors are spectrum colors so they are fully saturated. Therefore, the values shown of 255 applies the all circle regions. The center is white so its saturation should be 0.

(c) Give the gray level values of all regions in the intensity image.

The value of the both darker gray regions are 85. Equal proportions of the secondary’s yellow cyan and magenta produce white so the two lighter gray regions have the same value of 170 and the center of the image is white so its value should be 255. 



(3)	 [9%] Consider the following 500×500 RGB image, in which the squares are fully saturated red, green and blue, and each of the colors is at maximum intensity [e.g., (1, 0, 0) for the red square]. An HSI image is generated from this image. 
(a)	Describe the appearance of each HSI component image.
(b)	The saturation component of the HSI image is smoothed using an averaging mask of size 125×125. Describe the appearance of the result (you may ignore image border effects in the filtering operation). 
(c)	Repeat (b) for the hue image.






Answer 3:

(a)	Describe the appearance of each HSI component image

Red: 0,100,40
Green: 121,100,40
Blue: 236,100,40

For these given values after we make any process on them they change


(b)	The saturation component of the HSI image is smoothed using an averaging mask of size 125×125. Describe the appearance of the result (you may ignore image border effects in the filtering operation). 

Blurring don’t effect in this case. The I image is constant so values are at their maximum because of that pure colors are fully saturated.

(d)	Repeat (b) for the hue image.

The boundary between red and green becomes thickened and yellow also the boundary between green and blue similarly blurred in cyan.



Part B: (47%) DCT based image compression

Description: DCT transformation refers to the transform between image spatial domain and frequency domain. In the first part of the assignment, you are required to realize a simplified version of DCT based compression. 

(I)	(15%) Consider the following sequence of values: 

10	  11    12  11  12  13  12  11
                   10  -10      8   -7   8   -8   7   -7

	I used this formula for 1d DCT:

	

(a)	(5%) Transform each row separately using an eight-point DCT. Plot the resulting 16 transform coefficients









(b)	(5%) Combine all 16 numbers into a single vector and transform it using a 16-point DCT. Plot the 16 transform coefficients



(c)	(5%) Compare the results of (a) and (b). For this particular case would you suggest a block size of 8 or 16 for greater compression? Justify your answer

I suggest block size 8 makes greater compression because it gives higher value of 32 besides 16 one gives 22 or so. With that information we can clearly understand that first one is much greater for compression to the other. When peak is greater the compression is also greater.


(II)	(32%) 2D image compression:  
(1)	Obtain image f1 (“basel2.bmp”) and display;


			F1: Basel2.bmp

(2)	(5%) Convert image f1 from RGB to HSI, obtain intensity image I.

			I: Basel2 HSI

(3)	(6%) Apply 8*8 DCT transform to image I, obtain frequency domain image F; 
(4)	(6%) In each 8*8 frequency block, keep DC component and remove all other frequency components from F, obtain frequency domain image D1; 
(5)	(6%) Similar to (4), in each 8*8 frequency block, keep first 9 low frequency components and remove all other high frequency components from F, obtain frequency domain image D2;
(6)	(9%) Apply IDCT on D1 and D2, obtain image R1 and R2. Explain which image is more blurred, and why.

Part B: (20%) Color based image segmentation 

Image segmentation can be realized based on the color information processing. In this assignment, you are required to design an algorithm to use the HSI model to detect the regions of interest (ROI). 

Implement your algorithm to segment the regions in “Bulding1.bmp” and “Plate.bmp”. Outline the boundaries of each ROI. Describe your algorithm and the results in your report.  (Hint: You may consider the HSI model and Hough transform)


Answer Part B:

For this part first I used HSI model to translate my image to RGB to HSI for reach my goal I used simply RGB to HSI algorithm (http://answers.opencv.org/question/62446/conversion-from-rgb-to-hsi/ ). Than after I get the image I want I used SOBEL operator which  I used in the second assignment to find ROI`s. With a little changing to my SOBEL operator I used it just for intensity image to get sharp results.


