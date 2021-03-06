<img src="readme_images/title.png" alt="Displays the title OpenAlice"> 

<h1> What is OpenAlice? </h1>
<p> OpenAlice is a open source game written in C++ that is heavily inspired by the 2007 game Alice Greenfingers. In OpenAlice you control Alice, a scarecrow who wants to plant crops and watch them grow. Once they mature, Alice can sell her produce at the market. </p>

<h1> How To Play </h1>
<ul>
 <li> Pressing the Q key picks up an item. </li>
 <li> Pressing the E key uses said item. You can refill your watering can when it is empty by clicking E next to the well while you are holding it. You can go to sleep by pressing E next to Alice's house while you have no items in your hands. </li>
 <li> You can till soil by using the hoe on grass and plant seeds by using them on tilled dirt. </li>
 <li> Water your plants every day so that they grow big and produce lots of crops! </li>
 <li> Harvest your crops by placing them in crates to be sold! Crates fill once they have  10 vegetables inside. </li>
 <li> Going to sleep saves your progress, so don't quit without going to sleep first! </li>
</ul>

<h1> Windows 10 (64 Bit) Installation </h1>

<h2> Simple Installation </h2>
<p> First, clone the repository to your computer. Navigate to the folder where you want to keep the OpenAlice files and run the following command.</p>
<h6> git clone https://github.com/SeanTheSheepCS/OpenAlice.git </h6>
<p> Second, navigate into the OpenAlice directory. </p>
<h6> cd OpenAlice </h6>
<p> Third, move to the Windows 10 Release 64 bit branch. </p>
<h6> git checkout windows_10_64_bit_v1 </h6>
<p> Lastly, go to the folder called game and click on alice_game.exe. </p>

<h2> Compile-It-Yourself Installation </h4>
<p> To compile the code yourself, please install Make along with the following two zipped files and extract them. </p>
<ul>
 <li> MINGW GCC 7.3.0 for Windows 10 64 bit, available here: https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-posix/seh/x86_64-7.3.0-release-posix-seh-rt_v5-rev0.7z/download </li>
 <li> SFML for Windows 10 64 Bit GCC 7.3.0. Please click the download link that says GCC 7.3.0 MinGW (SEH) - 64-bit. Download links avaiable here: https://www.sfml-dev.org/download/sfml/2.5.1/ </li>
</ul>
<p> By this step, you should have two files, one called "mingw64" and one called "SFML-2.5.1". Place those two folders wherever you please, but remember where you put them. Next, clone this repository to your computer by running the following command. </p>
<h6> git clone https://github.com/SeanTheSheepCS/OpenAlice.git </h6>
<p> Next, go to the build_windows_10 folder and open the Makefile because we will need to make modifications to it. </p>
<ul>
 <li> Modification 1: Change the first line of the Makefile to reflect the location of your SFML installation. For example, if you downloaded SFML to the folder C:/Users/Tom/Desktop/, you would change the first line to "IPATH=C:/Users/Tom/Desktop/SFML-2.5.1/include"</li>
 <li> Modification 2: Change the seventh line of the Makefile to reflect the location of your SFML installation. For example, if you downloaded SFML to the folder D:/Libraries/, you would change the seventh line to "LPATH=D:/Libraries/SFML-2.5.1/lib"</li>
 <li> Modification 3: Change the ninth line of the Makefile to reflect the location of your MINGW64-GCC7.3.0 installation. For example, if you downloaded MINGW64-GCC7.3.0 to the folder C:/BigFolder/SmallFolder/, you would change the ninth line to "CXX=C:/BigFolder/SmallFolder/mingw64/bin/g++.exe"</li>
</ul>
<p> Next, navigate to the bin folder inside the SFML-2.5.1 folder and copy all of the .dll files there into the build_windows_10 directory of OpenAlice. </p>
<p> After these changes, please run the following command inside the build_windows_10 directory. </p>
<h6> make alice_game </h6>
<p> After the code has compiled, run alice_game.exe.</p>
<h1> Ubuntu 20 (64 Bit) Installation </h3>
<h2> Simple Installation </h4>
<p> First, you need to install SFML to your computer. You can do that by running the following command: </p>
<h6> sudo apt-get install libsfml-dev </h6>
<p> Then, you need to clone the repository and switch to the correct branch by running the following commands: </p>
<h6> git clone https://github.com/SeanTheSheepCS/OpenAlice.git </h6>
<h6> cd OpenAlice </h6>
<h6> git checkout ubuntu_20_64_bit_v1 </h6>
<p> To run the game afterwards, all you have to do is type the following command </p>
<h6> ./game/alice_game </h6>
<h2> Compile-It-Yourself Installation </h4>
<p> You need to install three things to make the compile-it-yourself version work. </p>
<ul>
 <li> 
  <p> SFML, we will install it once for it's headers and so that we can link to it, and then once more for usage after we no longer need to compile our code. </p>
  <p> Install one can be installed from https://www.sfml-dev.org/download/sfml/2.5.1/ by choosing the "Linux GCC-64 bit" option. Please extract this file and put it in a place that you will remember, we will need to know it's path for later steps. After you can run OpenAlice successfully, feel free to remove this install, we will only need the second one. </p>
  <p> Install two can be installed by running the following command: </p>
  <h6> sudo apt-get install libsfml-dev </h6>
 </li>
 <li>
  <p> Make, which can be installed by running the following command: </p>
  <h6> sudo apt-get install make </h6>
 </li>
 <li>
  <p> G++, which can be installed by running the following command: </p>
  <h6> sudo apt-get install g++ </h6>
 </li>
</ul>
<p> After all the installations, please clone the OpenAlice repository by running the following command </p>
<h6> git clone https://github.com/SeanTheSheepCS/OpenAlice.git </h6>
<p> Navigate to the build_ubuntu_20 folder by running the following command: </p>
<h6> cd OpenAlice/build_ubuntu_20 </h6>
<p> There is a Makefile in that folder. Please make the following modifications to the Makefile. </p>
<ul>
 <li> Modification 1: Change the first line of the Makefile to reflect the location of your SFML installation. For example, if you downloaded SFML to the folder ~/Desktop/MyFolder, you would change the first line to "IPATH=~/Desktop/MyFolder/SFML-2.5.1/include"</li>
 <li> Modification 2: Change the seventh line of the Makefile to reflect the location of your SFML installation. For example, if you downloaded SFML to the folder ~/Desktop/, you would change the seventh line to "LPATH=~/Desktop/SFML-2.5.1/lib"</li>
</ul>
<p> After these modifications, please run the following command. </p>
<h6> make alice_game </h6>
<p> Lastly, OpenAlice can be started by running the following command. </p>
<h6> ./alice_game </h6>

<h1> What Libraries Does OpenAlice Use? </h1>
<p> OpenAlice uses SFML for graphics and audio. The following link will take you to a page that contains tutorials on using SFML and a link where you can donate to the creators of this library. https://www.sfml-dev.org/ </p>

<h1> License </h1>
<p> 
  OpenAlice has been released into the public domain. Anyone is free to use, modify, or distribute this work for any purpose. The Unlicense applies to the source code and a zlib/png license applies to the SFML library which this game depends on. If I have made a licensing mistake or any mistakes in the proper procedure for releasing the contents of this repository to the public domain, please contact me by opening up an issue on this repository. 
</p>
<p xmlns:dct="http://purl.org/dc/terms/" xmlns:vcard="http://www.w3.org/2001/vcard-rdf/3.0#">
  <a rel="license"
     href="http://creativecommons.org/publicdomain/zero/1.0/">
    <img src="http://i.creativecommons.org/p/zero/1.0/88x31.png" style="border-style: none;" alt="CC0" />
  </a>
  <br />
  To the extent possible under law,
  <a rel="dct:publisher"
     href="https://github.com/SeanTheSheepCS/">
    <span property="dct:title">Sean Kenny</span></a>
  has waived all copyright and related or neighboring rights to
  <span property="dct:title">OpenAlice</span>.
This work is published from:
<span property="vcard:Country" datatype="dct:ISO3166"
      content="CA" about="https://github.com/SeanTheSheepCS/OpenAlice/">
  Canada</span>.
<h4> If you are curious about any aspect of OpenAlice, please open up an issue on this repository with your question. </h4>
<h4> Thank you for interest in OpenAlice! </h4>
</html>
