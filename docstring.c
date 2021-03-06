/*
    FLAM3 - cosmic recursive fractal flames
    Copyright (C) 1992-2009 Spotworks LLC

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "config.h"
#include "flam3.h"


static char *the_docstring0 =
  "FLAM3 - cosmic recursive fractal flames version ";

static char *the_docstring1 =
"\n\n"
"This software is licensed under the GPL.  You should have access\n"
"to the source code; see http://www.fsf.org/licenses/gpl.html.\n"
"\n"
"This is free software to render fractal flames as described on\n"
"http://flam3.com.  Flam3-animate makes animations, and flam3-render\n"
"makes still images.  Flam3-genome creates and manipulates genomes\n"
"(parameter sets).  A C library is also installed.\n"
"\n"
"Note: the following instructions are written for Linux users.  Windows\n"
"users may have to install the cygwin package to get the \"env\"\n"
"command or set the envars in your windows command prompt manually.\n"
"That means instead of a command like\n"
"\n"
"    env dtime=5 prefix=foo. in=test.flame flam3-animate\n"
"\n"
"use the following set of commands:\n"
"\n"
"    set dtime=5\n"
"    set prefix=foo.\n"
"    set in=test.flame\n"
"    flam3-animate\n"
"\n"
"\n"
"envar           default     meaning\n"
"=====           =======     =======\n"
"prefix          (empty)     prefix names of output files with this string.\n"
"begin           j           time of first frame to render (j=first time specified in file) (animate only)\n"
"end             n-1         time of last frame to render (n=last time specified in the input file) (animate only)\n"
"time            NA          time of first and last frame (ie do one frame) (animate only)\n"
"frame           NA          synonym for \"time\" (animate only)\n"
"in              stdin       name of input file\n"
"out             NA          name of output file (bad idea if rending more than one, use prefix instead)\n"
"template        NA          apply defaults based on this genome (genome only)\n"
"dtime           1           time between frames (animate only)\n"
"fields          0           if 1 then render fields, ie odd scanlines at time+0.5\n"
"nstrips         1           number of strips, ie render fractions of a frame at once (render only)\n"
"qs              1           quality scale, multiply quality of all frames by this\n"
"ss              1           size scale, multiply size (in pixels) of all frames by this\n"
"jpeg            NA          jpeg quality for compression, default is native jpeg default\n"
"format          png         jpg or ppm or png\n"
"pixel_aspect    1.0         aspect ratio of pixels (width over height), eg 0.90909 for NTSC\n"
"seed            random      integer seed for random numbers, defaults to time+pid\n"
"isaac_seed      random      character-based seed for iteration loop randomness, defaults to time\n"
"nthreads        0           number of threads to use for render.  default auto-detects.\n"
"verbose         0           if non-zero then print progress meter on stderr\n"
"bits            33          also 32 or 64: sets bit-width of internal buffers (33 means 32-bit floating-point)\n"
"bpc             8           bits per color channel: png supports 16, all others are 8 only (render/animate)\n"
"image           filename    replace palette with png, jpg, or ppm image\n"
"use_vars        -1          comma separated list of variation #'s to use when generating a random flame (genome only)\n"
"dont_use_vars   NA          comma separated list of variation #'s to NOT use when generating a random flame (genome only)\n"
"cross0          NA          randomly select one genome from this file to genetically cross (genome only)\n"
"cross1          NA            with one genome from this file (genome only)\n"
"method          NA          method used for genetic cross: alternate, interpolate, or union. (genome only)\n"
"mutate          NA          randomly mutate a random genome from this file (genome only)\n"
"symmetry        NA          set symmetry of result. (genome only)\n"
"clone           NA          clone random flame in input (genome only)\n"
"clone_all       NA          clones all flames in file.  useful for applying template to all flames (genome only)\n"
"animate         NA          interpolates between all flames in a file, using times specified in file (genome only)\n"
"sequence        NA          360 degree rotation 'loops' times of each control point plus rotating transitions (genome only)\n"
"loops           NA          number of times to rotate each control point in sequence (genome only)\n"
"tries           50          number of tries to make to find a good genome. (genome only)\n"
"strip           NA          strip input, frame and nframes control which one. (genome only)\n"
"transparency    0           make bknd transparent, if format supports it (render/animate)\n"
"name_enable     0           use 'name' attr in <flame> to name image output if present (render only)\n"
"nick            \"\"          nickname to use in <edit> tags / img comments\n"
"url             \"\"          url to use in <edit> tags / img comments\n"
"id              \"\"          ID to use in <edit> tags\n"
"comment         \"\"          comment string for <edit> tags (genome only)\n"
"use_mem         auto        floating point number of bytes of memory to use (render only)\n"
"write_genome    0           write out genome associated with center of motion blur window (animate only)\n"
"noedits         unset       omit edit tags from output (genome only)\n"
"print_edit_depth 0          depth to truncate <edit> tag structure.  0 prints all <edit> tags (genome only)\n"
"flam3_palettes  unset       location of flam3-palettes.xml if not at default install location\n"
"intpalette      unset       round palette entries for importing into older Apophysis versions (genome only)\n"
"insert_palette  unset       insert the palette into the image.\n"
"enable_jpeg_comments   1    enables comments in the jpeg header (render and animate)\n"
"enable_png_comments    1    enables comments in the png header (render and animate)\n"
"\n"
"earlyclip       0               enables the early clipping of rgb values for better antialiasing and resizing\n"
"                                defaults to 0 for backwards compatibility\n"
"flam27          0               flam3 2.7 compatibility mode; ensures generated genomes can be used by flam3 2.7.18\n"
"stagger         0               affects simultaneity of xform interpolation during genome interpolation.\n"
"                                represents how 'separate' the xforms are interpolated.  set to 1 for each\n"
"                                xform to be interpolated individually, fractions control interp overlap.\n"
"apo_palette     0               set this to 1 to use only the first 255 elements of the palette (apophysis compatibility)\n"

"\n"
"for example:\n"
"\n"
"    env dtime=5 prefix=foo. in=test.flam3 flam3-animate\n"
"\n"
"means to render every 5th frame of parameter file foo.flam3, and store\n"
"the results in files named foo.XXXX.jpg.\n"
"\n"
"the flam3-convert program reads from stdin the old format created by\n"
"the GIMP and writes to stdout the new xml format.\n"
"\n"
"the flam3-genome program creates random parameter files. it also mutates,\n"
"rotates, and interpolates existing parameter files.  for example to\n"
"create 10 wholly new control points and render them at normal quality:\n"
"\n"
"    env template=vidres.flam3 repeat=10 flam3-genome > new.flam3\n"
"    flam3-render < new.flam3\n"
"\n"
"if you left out the \"template=vidres.flam3\" part then the size,\n"
"quality, etc parameters would be their default (small) values.  you\n"
"can set the symmetry group:\n"
"\n"
"    env template=vidres.flam3 symmetry=3 flam3-genome > new3.flam3\n"
"    env template=vidres.flam3 symmetry=-2 flam3-genome > new-2.flam3\n"
"    flam3-render < new3.flam3\n"
"    flam3-render < new-2.flam3\n"
"\n"
"Mutation is done by giving an input flame file to alter:\n"
"\n"
"    env template=vidres.flam3 flam3-genome > parent.flam3\n"
"    env prefix=parent. flam3-render < parent.flam3\n"
"    env template=vidres.flam3 mutate=parent.flam3 repeat=10 flam3-genome > mutation.flam3\n"
"    flam3-render < mutation.flam3\n"
"\n"
"Normally one wouldn't use the same file for the template and the file\n"
"to mutate.  Crossover is handled similarly:\n"
"\n"
"    env template=vidres.flam3 flam3-genome > parent0.flam3\n"
"    env prefix=parent0. flam3-render < parent0.flam3\n"
"    env template=vidres.flam3 flam3-genome > parent1.flam3\n"
"    env prefix=parent1. flam3-render < parent1.flam3\n"
"    env template=vidres.flam3 cross0=parent0.flam3 cross1=parent1.flam3 flam3-genome > crossover.flam3\n"
"    flam3-render < crossover.flam3\n"
"\n"
"flam3-genome has 3 ways to produce parameter files for animation in\n"
"the style of electric sheep.  the highest level and most useful from\n"
"the command line is the sequence method.  it takes a collection of\n"
"control points and makes an animation that has each flame do fractal\n"
"rotation for 360 degrees, then make a smooth transition to the next.\n"
"for example:\n"
"\n"
"    env sequence=test.flam3 nframes=20 flam3-genome > seq.flam3\n"
"    flam3-animate < seq.flam3\n"
"\n"
"creates and renders a 60 frame animation.  there are two flames in\n"
"test.flam3, so the animation consists three stags: the first one\n"
"rotating, then a transition, then the second one rotating.  each stage\n"
"has 20 frames as specified on the command line.  if you want to\n"
"render only some fraction of a whole animation file, specify the begin\n"
"and end times:\n"
"\n"
"    env begin=20 end=40 flam3-animate < seq.flam3\n"
"\n"
"the other two methods are harder to use becaues they produce files that\n"
"are only good for one frame of animation.  the output consists of 3\n"
"control points, one for the time requested, one before and one after.\n"
"that allows proper motion blur.  for example:\n"
"\n"
"    env template=vidres.flam3 flam3-genome > rotme.flam3\n"
"    env rotate=rotme.flam3 frame=10 nframes=20 flam3-genome > rot10.flam3\n"
"    env frame=10 flam3-animate < rot10.flam3\n"
"\n"
"the file rot10.flam3 specifies the animation for just one frame, in\n"
"this case 10 out of 20 frames in the complete animation.  C1\n"
"continuous electric sheep genetic crossfades are created like this:\n"
"\n"
"    env inter=test.flam3 frame=10 nframes=20 flam3-genome > inter10.flam3\n"
"    env frame=10 flam3-animate < inter10.flam3\n"
"\n"
"see http://flam3.com/flame.pdf for descriptions & formulas, and\n"
"see http://electricsheep.wikispaces.com/Variations for updates.\n"
"\n"
"The complete list of variations:\n"
;

void docstring() {
    int i;
    fputs(the_docstring0, stdout);
    fputs(flam3_version(), stdout);
    fputs(the_docstring1, stdout);
    for (i = 0; i < flam3_nvariations; i++)
   printf("  %2d. %s\n", i, flam3_variation_names[i]);
}
