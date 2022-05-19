# Parallel Median Filter
The median filter is a nonlinear digital filtering technique, often used to remove 
noise from an image or signal. Such noise reduction is a typical pre-processing 
step to improve the results of later processing.

# Requirement
• Size of window is dynamic (9,25,49,..).

• Render your results.

• Test your code with these different conditions:

   1- different image sizes (e.g if the image size is N * N, so test your code if the image size is 5N * 5N and 10N * 10N).
  
   2- different image size with multiple images (e.g 10 images of size 5N * 5N).
  
• Record your Results.

| requirment        |    1 pic N* N   | 1 pic 5N* 5N    | 1 pic 10N* 10N  | 10 pics 5N* 5N |    
| :---------------: | :-------------: | :-------------: | :-------------: | :------------: | 
| `sequential code` |      799        |      18748      |      38289      |       53884    |
| `MPI Sol1`        |      734        |      13260      |      30118      |                |

# Notes
1- For 1 pic (N * N) and 1 pic (5N * 5N), we use (7 * 7) mask.

2- For 1 pic (10N * 10N), we use (5 * 5) mask.

3- For 10 pics (5N * 5N), we use (3 * 3) mask.

