# Final-project-in-image-processing
Final project in image processing course.

# **EngageYa SDK**

### **Installation Guide:**

- Open **EngageYa-SDK.proj**
- Build your project for:

	-**iOS devices** Build with **Generic iOS Device.**.
	
	-**Simulators** build it with one of the simulators.
	
	
	
**If do you want that the framework will be universal you need to follow about these steps:**
	
**----------------------------------------------------------------------------------------------------------------------**	
1. Build EngageYa_SDK target for iOS simulator and extract a framework from the products folder on your desktop.

2. Rename the framework to EngageYa_SDK-sim.framework so that it is distinguishable later.

3. Repeat steps 1 and 2 for the iOS device. You can select ‘Generic iOS Device’. Don’t forget to rename the framework to EngageYa_SDK-dev.framework .

4. Use the following command to combine both binaries into a single fat binary file (Make sure you are on the desktop while running this command): 
**lipo -create ./EngageYa_SDK-sim.framework/EngageYa_SDK ./EngageYa_SDK-dev.framework/EngageYa_SDK -output ./EngageYa_SDK**
5.  Copy EngageYa_SDK binary file created in the above step and replace it with the binary in EngageYa_SDK-dev.framework folder.
6.  Open ‘Info.plist’ the file contained in the same folder.
7. Add ‘iPhoneSimulator’ string in ‘CFBundleSupportedPlatforms’ array.
8. The final plist file would look like this:
![Screen Shot 2019-07-17 at 17 15 07](https://user-images.githubusercontent.com/18244088/61382975-71e72a00-a8b6-11e9-93a7-48afafe08b27.png)

 9. From folder :

		EngageYa_SDK-sim.framework/Modules/EngageYa_SDK.swiftmodule/
		
	**copy ‘x86_64.swiftdoc’ and ‘x86_64.swiftmodule’ and paste them to:**
		
		EngageYa_SDK-dev.framework/Modules/EngageYa_SDK.swiftmodule/

10. By following the above steps you have converted EngageYa_SDK-dev.framework from device only to a universal fat framework. Rename it to EngageYa_SDK.framework .

**----------------------------------------------------------------------------------------------------------------------**

- Open the Products folder.
- Right Click on the **EngageYa_SDK.framework** -> show in finder to get the path of the framework.


**Inside of the project that you want to implement EngageYa SDK:**

- Drag the **EngageYa_SDK.framework** file into your **Embedded Binaries.** .
- In your **info.Plist** you will need to add :

   ![Screen Shot 2](https://user-images.githubusercontent.com/18244088/61183111-8a9cd900-a645-11e9-8dba-d6db5a4d7bc0.png)
	
   Or add to the info.plist source code: 

   ![Screen Shot 1](https://user-images.githubusercontent.com/18244088/61183085-3134aa00-a645-11e9-88c6-09c239c70e00.png)


### **AppDelegate:**

- Import **EngageYa_SDK** into the **AppDelegate.swift**
- Initialize the SDK with your 4 parameters:
- Add to didFinishLaunchingWithOptions:

    ![Screen Shot 3](https://user-images.githubusercontent.com/18244088/61183112-8cff3300-a645-11e9-9434-33b237741ad9.png)

### **Implemantation of EngageYa WebView:**

1.Import **EngageYa_SDK**

2.Conform the EngageYaWebViewDelegate protocol:
```swift
	EngageYaWebView(userDelegate: EngageYaWebViewDelegate)
 ```
```swift
	- onStoryOpen()- Called when the user clicked a story.
	- onStoryClose()- Called when the user closed a story.
	- onCallToActionOpen()- Called when the user link inside one of the stories.
	- onCallToActionClose()- Called when the user return from external link.
	- webViewDidLoadSuccess()- Called when EngageYa webView load Success.
	- webViewDidLoadFail()- Called when EngageYa webView failed to load and return the Error.
 ```
3.Create your webView.
 
4.Initialize your webView with your **EngageYaWebViewDelegate**: 
```swift
	EngageYaWebView(userDelegate: EngageYaWebViewDelegate)
```
