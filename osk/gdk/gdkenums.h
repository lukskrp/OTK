/* GDK - The GIMP Drawing Kit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Modified by the GTK+ Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GTK+ Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GTK+ at ftp://ftp.gtk.org/pub/gtk/.
 */

#pragma once

#if !defined (__GDK_H_INSIDE__) && !defined (GTK_COMPILATION)
#error "Only <gdk/gdk.h> can be included directly."
#endif

#include <glib.h>

#include <gdk/version/gdkversionmacros.h>

G_BEGIN_DECLS

/**
 * GdkColorChannel:
 * @GDK_COLOR_CHANNEL_RED: The red color channel, aka 0
 * @GDK_COLOR_CHANNEL_GREEN: The green color channel, aka 1
 * @GDK_COLOR_CHANNEL_BLUE: The blue color channel, aka 2
 * @GDK_COLOR_CHANNEL_ALPHA: The alpha color channel, aka 3
 *
 * Enumerates the color channels of RGBA values as used in
 * `GdkColor` and OpenGL/Vulkan shaders.
 *
 * Note that this is not the order of pixel values in Cairo
 * and `GdkMemoryFormat` can have many different orders.
 *
 * Since: 4.22
 */
typedef enum {
  GDK_COLOR_CHANNEL_RED GDK_AVAILABLE_ENUMERATOR_IN_4_22 = 0,
  GDK_COLOR_CHANNEL_GREEN GDK_AVAILABLE_ENUMERATOR_IN_4_22 = 1,
  GDK_COLOR_CHANNEL_BLUE GDK_AVAILABLE_ENUMERATOR_IN_4_22 = 2,
  GDK_COLOR_CHANNEL_ALPHA GDK_AVAILABLE_ENUMERATOR_IN_4_22 = 3
} GdkColorChannel;

/**
 * GdkGLAPI:
 * @GDK_GL_API_GL: The OpenGL API
 * @GDK_GL_API_GLES: The OpenGL ES API
 *
 * The list of the different APIs that GdkGLContext can potentially support.
 *
 * Since: 4.6
 */
typedef enum { /*< underscore_name=GDK_GL_API >*/
  GDK_GL_API_GL   = 1 << 0,
  GDK_GL_API_GLES = 1 << 1
} GdkGLAPI;

/* Currently, these are the same values numerically as in the
 * X protocol. If you change that, gdksurface-x11.c/gdk_surface_set_geometry_hints()
 * will need fixing.
 */
/* OSK: GdkGravity is ODK's (gdk/gdktypes.h) */

/* Types of modifiers.
 */
/* OSK: GdkModifierType is ODK's (gdk/gdktypes.h) */


/**
 * GDK_MODIFIER_MASK:
 *
 * A mask covering all entries in `GdkModifierType`.
 */
#define GDK_MODIFIER_MASK (GDK_SHIFT_MASK|GDK_LOCK_MASK|GDK_CONTROL_MASK| \
                           GDK_ALT_MASK|GDK_SUPER_MASK|GDK_HYPER_MASK|GDK_META_MASK| \
                           GDK_BUTTON1_MASK|GDK_BUTTON2_MASK|GDK_BUTTON3_MASK| \
                           GDK_BUTTON4_MASK|GDK_BUTTON5_MASK)


/**
 * GdkDmabufError:
 * @GDK_DMABUF_ERROR_NOT_AVAILABLE: Dmabuf support is not available, because the OS
 *   is not Linux, or it was explicitly disabled at compile- or runtime
 * @GDK_DMABUF_ERROR_UNSUPPORTED_FORMAT: The requested format is not supported
 * @GDK_DMABUF_ERROR_CREATION_FAILED: GTK failed to create the resource for other
 *   reasons
 *
 * Error enumeration for `GdkDmabufTexture`.
 *
 * Since: 4.14
 */
typedef enum {
  GDK_DMABUF_ERROR_NOT_AVAILABLE,
  GDK_DMABUF_ERROR_UNSUPPORTED_FORMAT,
  GDK_DMABUF_ERROR_CREATION_FAILED,
} GdkDmabufError;

/* OSK: GdkGLError is ODK's (gdk/gdktypes.h) */

/**
 * GdkVulkanError:
 * @GDK_VULKAN_ERROR_UNSUPPORTED: Vulkan is not supported on this backend or has not been
 *   compiled in.
 * @GDK_VULKAN_ERROR_NOT_AVAILABLE: Vulkan support is not available on this Surface
 *
 * Error enumeration for `GdkVulkanContext`.
 */
typedef enum {
  GDK_VULKAN_ERROR_UNSUPPORTED,
  GDK_VULKAN_ERROR_NOT_AVAILABLE,
} GdkVulkanError;

/* OSK: GdkAxisUse is ODK's (gdk/gdktypes.h) */

/* OSK: GdkAxisFlags is ODK's (gdk/gdktypes.h) */

/* OSK: GdkDragAction is ODK's (gdk/gdktypes.h) */

/**
 * GdkScrollRelativeDirection:
 * @GDK_SCROLL_RELATIVE_DIRECTION_IDENTICAL: Physical motion and event motion are the same
 * @GDK_SCROLL_RELATIVE_DIRECTION_INVERTED: Physical motion is inverted relative to event motion
 * @GDK_SCROLL_RELATIVE_DIRECTION_UNKNOWN: Relative motion is unknown on this device or backend
 *
 * Used in scroll events, to announce the direction relative
 * to physical motion.
 *
 * Since: 4.20
 */
typedef enum
{
  GDK_SCROLL_RELATIVE_DIRECTION_IDENTICAL,
  GDK_SCROLL_RELATIVE_DIRECTION_INVERTED,
  GDK_SCROLL_RELATIVE_DIRECTION_UNKNOWN,
} GdkScrollRelativeDirection;

/**
 * GDK_ACTION_ALL:
 *
 * Defines all possible DND actions.
 *
 * This can be used in [method@Gdk.Drop.status] messages when any drop
 * can be accepted or a more specific drop method is not yet known.
 */
#define GDK_ACTION_ALL (GDK_ACTION_COPY | GDK_ACTION_MOVE | GDK_ACTION_LINK)

/**
 * GdkFrameResult:
 *
 * An enumeration describing the process of rendering a frame.
 * Rendering a frame starts with the frame clock cycle and then follows
 * the rendered frame (if there was one) through the display server
 * until it appears on screen.
 *
 * It is relevant in particular for [struct@Gdk.FrameTimings] which
 * may still be waiting for values to be filled in.
 *
 * Since: 4.24
 */
/**
 * GDK_FRAME_PREPARING:
 *
 * The frame is currently being prepared and rendered by GTK.
 * This is the initial state.
 *
 * Since: 4.24
 */
/**
 * GDK_FRAME_SKIPPED:
 *
 * GTK has determined that nothing needs to be rendered because
 * there are no visual changes. No rendering will be submitted to
 * the display server and because of that no information will
 * be forthcoming from the display server.
 *
 * The frame is complete.
 *
 * Since: 4.24
 */
/**
 * GDK_FRAME_EMPTY:
 *
 * GTK has determined that nothing needs to be rendered because
 * there are no visual changes. This information has been submitted 
 * to the display server. The presentation time has been updated to
 * reflect when this frame would have been displayed.
 *
 * The frame is complete.
 *
 * Since: 4.24
 */
/**
 * GDK_FRAME_SUBMITTED:
 *
 * A frame has been drawn and submitted to the display server, but
 * the display server will not provide any further feedback about when
 * or how the frame is going to be displayed.
 *
 * The frame is complete.
 *
 * Since: 4.24
 */
/**
 * GDK_FRAME_OUTSTANDING:
 *
 * The frame has been drawn and submitted to the display server, but the
 * display server has not yet replied what is going to happen with the
 * rendered image.
 *
 * Since: 4.24
 */
/**
 * GDK_FRAME_DISCARDED:
 *
 * The frame has been drawn and submitted to the display server, but the
 * display server has not displayed it. No presentation time will be available.
 *
 * The frame is complete.
 *
 * Since: 4.24
 */
/**
 * GDK_FRAME_PRESENTED:
 *
 * The frame has been drawn and submitted to the display server, and the
 * display server has rendered it and displayed the result. The presentation
 * time is accurately reflecting when that happened.
 *
 * The frame is complete.
 *
 * Since: 4.24
 */
typedef enum {
  GDK_FRAME_PREPARING,
  GDK_FRAME_SKIPPED,
  GDK_FRAME_EMPTY,
  GDK_FRAME_SUBMITTED,
  GDK_FRAME_OUTSTANDING,
  GDK_FRAME_DISCARDED,
  GDK_FRAME_PRESENTED,
} GdkFrameResult;

/**
 * GdkMemoryFormat:
 * @GDK_MEMORY_B8G8R8A8_PREMULTIPLIED: 4 bytes; for blue, green, red, alpha.
 *   The color values are premultiplied with the alpha value.
 * @GDK_MEMORY_A8R8G8B8_PREMULTIPLIED: 4 bytes; for alpha, red, green, blue.
 *   The color values are premultiplied with the alpha value.
 * @GDK_MEMORY_R8G8B8A8_PREMULTIPLIED: 4 bytes; for red, green, blue, alpha
 *   The color values are premultiplied with the alpha value.
 * @GDK_MEMORY_B8G8R8A8: 4 bytes; for blue, green, red, alpha.
 * @GDK_MEMORY_A8R8G8B8: 4 bytes; for alpha, red, green, blue.
 * @GDK_MEMORY_R8G8B8A8: 4 bytes; for red, green, blue, alpha.
 * @GDK_MEMORY_A8B8G8R8: 4 bytes; for alpha, blue, green, red.
 * @GDK_MEMORY_R8G8B8: 3 bytes; for red, green, blue. The data is opaque.
 * @GDK_MEMORY_B8G8R8: 3 bytes; for blue, green, red. The data is opaque.
 * @GDK_MEMORY_N_FORMATS: The number of formats. This value will change as
 *   more formats get added, so do not rely on its concrete integer.
 * @GDK_MEMORY_R32G32B32_FLOAT: 3 float values; for red, green, blue.
 *
 * Describes formats that image data can have in memory.
 *
 * It describes formats by listing the contents of the memory passed to it.
 * So `GDK_MEMORY_A8R8G8B8` will be 1 byte (8 bits) of alpha, followed by a
 * byte each of red, green and blue. It is not endian-dependent, so
 * `CAIRO_FORMAT_ARGB32` is represented by different `GdkMemoryFormats`
 * on architectures with different endiannesses.
 *
 * # A note on naming
 *
 * The format names are roughly modelled after
 * [VkFormat](https://www.khronos.org/registry/vulkan/specs/1.0/html/vkspec.html#VkFormat).
 * A name follows `GDK_MEMORY_<CHANNELS>_<DATA_TYPE>_<SUBSAMPLING> <PREMULTIPLIED>`
 * where CHANNELS describe how the RGBA channels are layed out in memory, with an
 * X denoting padding. DATA_TYPE is unsigned normalized integer if not present, or
 * otherwise FLOAT. The optional SUBSAMPLING defines the subsampling method used.
 * The optional ENDIAN term describes the endianness if it is not
 * host-endian. Finally, an optional PREMULTIPLIED term indicates that the color
 * channels are premultiplied with the alpha value, if it is omitted, the data is
 * not premultiplied or there is no alpha channel.
 *
 * The CHANNELS are given as a list of planes seperated by underscores where
 * each plane is split into multiple elements describing one or more bytes of memory.
 * Each element is given as the list of channels folowed by the amount of bits taken
 * up.
 *
 * So the fictional format `RGB565_A8_PREMULTIPLIED` would describe a format with 2
 * planes where the first plane is an unsigned 16 bit integer containing the RGB
 * channels with 5, 6, and 5 bits respectively while the 2nd plane contains the
 * alpha channel as an unisnged 8bit integer.
 */
/**
 * GDK_MEMORY_A8B8G8R8_PREMULTIPLIED:
 *
 * 4 bytes; for alpha, blue, green, red, The color values are premultiplied with
 * the alpha value.
 *
 * Since: 4.14
 */
/**
 * GDK_MEMORY_B8G8R8X8:
 *
 * 4 bytes; for blue, green, red, unused.
 *
 * Since: 4.14
 */
/**
 * GDK_MEMORY_X8R8G8B8:
 *
 * 4 bytes; for unused, red, green, blue.
 *
 * Since: 4.14
 */
/**
 * GDK_MEMORY_R8G8B8X8:
 *
 * 4 bytes; for red, green, blue, unused.
 *
 * Since: 4.14
 */
/**
 * GDK_MEMORY_X8B8G8R8:
 *
 * 4 bytes; for unused, blue, green, red.
 *
 * Since: 4.14
 */
/**
 * GDK_MEMORY_R16G16B16:
 *
 * 3 guint16 values; for red, green, blue.
 *
 * Since: 4.6
 */
/**
 * GDK_MEMORY_R16G16B16A16_PREMULTIPLIED:
 *
 * 4 guint16 values; for red, green, blue, alpha. The color values are
 * premultiplied with the alpha value.
 *
 * Since: 4.6
 */
/**
 * GDK_MEMORY_R16G16B16A16:
 *
 * 4 guint16 values; for red, green, blue, alpha.
 *
 * Since: 4.6
 */
/**
 * GDK_MEMORY_R16G16B16_FLOAT:
 *
 * 3 half-float values; for red, green, blue. The data is opaque.
 *
 * Since: 4.6
 */
/**
 * GDK_MEMORY_R16G16B16A16_FLOAT_PREMULTIPLIED:
 *
 * 4 half-float values; for red, green, blue and alpha. The color values are
 * premultiplied with the alpha value.
 *
 * Since: 4.6
 */
/**
 * GDK_MEMORY_R16G16B16A16_FLOAT:
 *
 * 4 half-float values; for red, green, blue and alpha.
 *
 * Since: 4.6
 */
/**
 * GDK_MEMORY_B32G32R32_FLOAT:
 *
 * 3 float values; for blue, green, red. The data is opaque.
 *
 * Since: 4.6
 */
/**
 * GDK_MEMORY_R32G32B32A32_FLOAT_PREMULTIPLIED:
 *
 * 4 float values; for red, green, blue and alpha. The color values are
 * premultiplied with the alpha value.
 *
 * Since: 4.6
 */
/**
 * GDK_MEMORY_R32G32B32A32_FLOAT:
 *
 * 4 float values; for red, green, blue and alpha.
 *
 * Since: 4.6
 */
/**
 * GDK_MEMORY_G8A8_PREMULTIPLIED:
 *
 * 2 bytes; for grayscale, alpha. The color values are premultiplied with the
 * alpha value.
 *
 * Since: 4.12
 */
/**
 * GDK_MEMORY_G8A8:
 *
 * 2 bytes; for grayscale, alpha.
 *
 * Since: 4.12
 */
/**
 * GDK_MEMORY_G8:
 *
 * One byte; for grayscale. The data is opaque.
 *
 * Since: 4.12
 */
/**
 * GDK_MEMORY_G16A16_PREMULTIPLIED:
 *
 * 2 guint16 values; for grayscale, alpha. The color values are premultiplied
 * with the alpha value.
 *
 * Since: 4.12
 */
/**
 * GDK_MEMORY_G16A16:
 *
 * 2 guint16 values; for grayscale, alpha.
 *
 * Since: 4.12
 */
/**
 * GDK_MEMORY_G16:
 *
 * One guint16 value; for grayscale. The data is opaque.
 *
 * Since: 4.12
 */
/**
 * GDK_MEMORY_A8:
 *
 * One byte; for alpha.
 *
 * Since: 4.12
 */
/**
 * GDK_MEMORY_A16:
 *
 * One guint16 value; for alpha.
 *
 * Since: 4.12
 */
/**
 * GDK_MEMORY_A16_FLOAT:
 *
 * One half-float value; for alpha.
 *
 * Since: 4.12
 */
/**
 * GDK_MEMORY_A32_FLOAT:
 *
 * One float value; for alpha.
 *
 * Since: 4.12
 */
/**
 * GDK_MEMORY_G8_B8R8_420:
 *
 * Multiplane format with 2 planes.
 *
 * The first plane contains the first channel, usually containing
 * luma values.
 * The second plane with interleaved chroma values, Cb followed by Cr.
 * Subsampled in both the X and Y direction.
 *
 * Commonly known by the fourcc "NV12".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G8_R8B8_420:
 *
 * Multiplane format with 2 planes.
 *
 * The first plane contains the first channel, usually containing
 * luma values.
 * The second plane with interleaved chroma values, Cr followed by Cb.
 * Subsampled in both the X and Y direction.
 *
 * Commonly known by the fourcc "NV21".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G8_B8R8_422:
 *
 * Multiplane format with 2 planes.
 *
 * The first plane contains the first channel, usually containing
 * luma values.
 * The second plane with interleaved chroma values, Cb followed by Cr.
 * Subsampled in the X direction.
 *
 * Commonly known by the fourcc "NV16".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G8_R8B8_422:
 *
 * Multiplane format with 2 planes.
 *
 * The first plane contains the first channel, usually containing
 * luma values.
 * The second plane with interleaved chroma values, Cr followed by Cb.
 * Subsampled in the X direction.
 *
 * Commonly known by the fourcc "NV61".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G8_B8R8_444:
 *
 * Multiplane format with 2 planes.
 *
 * The first plane contains the first channel, usually containing
 * luma values.
 * The second plane with interleaved chroma values, Cb followed by Cr.
 * This format is not subsampled.
 *
 * Commonly known by the fourcc "NV24".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G8_R8B8_444:
 *
 * Multiplane format with 2 planes.
 *
 * The first plane contains the first channel, usually containing
 * luma values.
 * The second plane with interleaved chroma values, Cr followed by Cb.
 * This format is not subsampled.
 *
 * Commonly known by the fourcc "NV42".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G10X6_B10X6R10X6_420:
 *
 * Multiplane format with 2 planes.
 *
 * Each channel is a 16 bit integer, but only the highest 10 bits are used.
 *
 * The first plane contains the first channel, usually containing
 * luma values.
 * The second plane with interleaved chroma values, Cr followed by Cb.
 * This format is not subsampled.
 *
 * Commonly known by the fourcc "P010".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G12X4_B12X4R12X4_420:
 *
 * Multiplane format with 2 planes.
 *
 * Each channel is a 16 bit integer, but only the highest 10 bits are used.
 *
 * The first plane contains the first channel, usually containing
 * luma values.
 * The second plane with interleaved chroma values, Cr followed by Cb.
 * This format is not subsampled.
 *
 * Commonly known by the fourcc "P012".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G16_B16R16_420:
 *
 * Multiplane format with 2 planes.
 *
 * Each channel is a 16 bit integer.
 *
 * The first plane contains the first channel, usually containing
 * luma values.
 * The second plane with interleaved chroma values, Cr followed by Cb.
 * This format is not subsampled.
 *
 * Commonly known by the fourcc "P016".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G8_B8_R8_410:
 *
 * Multiplane format with 3 planes.
 *
 * Each channel is a 8 bit integer.
 *
 * The first plane usually contains the luma channel. It is mapped
 * into the 2nd channel.
 *
 * The second plane usually contains the first chroma chanel.
 * Subsampled in both the X and Y direction with 4:1 ratio. It is
 * mapped into the 3rd channel.
 *
 * The third plane usually contains the second chroma channel.
 * Subsampled in both the X and Y direction with 4:1 ratio. It is
 * mapped into the 1st channel.
 *
 * Commonly known by the fourcc "YUV410".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G8_R8_B8_410:
 *
 * Multiplane format with 3 planes.
 *
 * Each channel is a 8 bit integer.
 *
 * The first plane usually contains the luma channel. It is mapped
 * into the 2nd channel.
 *
 * The second plane usually contains the second chroma chanel.
 * Subsampled in both the X and Y direction with 4:1 ratio. It is
 * mapped into the 1st channel.
 *
 * The third plane usually contains the first chroma channel.
 * Subsampled in both the X and Y direction with 4:1 ratio. It is
 * mapped into the 3rd channel.
 *
 * Commonly known by the fourcc "YVU410".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G8_B8_R8_411:
 *
 * Multiplane format with 3 planes.
 *
 * Each channel is a 8 bit integer.
 *
 * The first plane usually contains the luma channel. It is mapped
 * into the 2nd channel.
 *
 * The second plane usually contains the first chroma chanel.
 * Subsampled in the X direction with 4:1 ratio. It is
 * mapped into the 3rd channel.
 *
 * The third plane usually contains the second chroma channel.
 * Subsampled in the X direction with 4:1 ratio. It is
 * mapped into the 1st channel.
 *
 * Commonly known by the fourcc "YUV411".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G8_R8_B8_411:
 *
 * Multiplane format with 3 planes.
 *
 * Each channel is a 8 bit integer.
 *
 * The first plane usually contains the luma channel. It is mapped
 * into the 2nd channel.
 *
 * The second plane usually contains the second chroma chanel.
 * Subsampled in the X direction with 4:1 ratio. It is
 * mapped into the 1st channel.
 *
 * The third plane usually contains the first chroma channel.
 * Subsampled in the X direction with 4:1 ratio. It is
 * mapped into the 3rd channel.
 *
 * Commonly known by the fourcc "YVU411".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G8_B8_R8_420:
 *
 * Multiplane format with 3 planes.
 *
 * Each channel is a 8 bit integer.
 *
 * The first plane usually contains the luma channel. It is mapped
 * into the 2nd channel.
 *
 * The second plane usually contains the first chroma chanel.
 * Subsampled in both the X and Y direction. It is mapped into the
 * 3rd channel.
 *
 * The third plane usually contains the second chroma channel.
 * Subsampled in both the X and Y direction. It is mapped into the
 * 1st channel.
 *
 * Commonly known by the fourcc "YUV420".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G8_R8_B8_420:
 *
 * Multiplane format with 3 planes.
 *
 * Each channel is a 8 bit integer.
 *
 * The first plane usually contains the luma channel. It is mapped
 * into the 2nd channel.
 *
 * The second plane usually contains the second chroma chanel.
 * Subsampled in both the X and Y direction. It is mapped into the
 * 1st channel.
 *
 * The third plane usually contains the first chroma channel.
 * Subsampled in both the X and Y direction. It is mapped into the
 * 3rd channel.
 *
 * Commonly known by the fourcc "YVU420".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G8_B8_R8_422:
 *
 * Multiplane format with 3 planes.
 *
 * Each channel is a 8 bit integer.
 *
 * The first plane usually contains the luma channel. It is mapped
 * into the 2nd channel.
 *
 * The second plane usually contains the first chroma chanel.
 * Subsampled in the X direction. It is mapped into the 3rd channel.
 *
 * The third plane usually contains the second chroma channel.
 * Subsampled in the X direction. It is mapped into the 1st channel.
 *
 * Commonly known by the fourcc "YUV422".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G8_R8_B8_422:
 *
 * Multiplane format with 3 planes.
 *
 * Each channel is a 8 bit integer.
 *
 * The first plane usually contains the luma channel. It is mapped
 * into the 2nd channel.
 *
 * The second plane usually contains the second chroma chanel.
 * Subsampled in the X direction. It is mapped into the 1st channel.
 *
 * The third plane usually contains the first chroma channel.
 * Subsampled in the X direction. It is mapped into the 3rd channel.
 *
 * Commonly known by the fourcc "YVU422".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G8_B8_R8_444:
 *
 * Multiplane format with 3 planes.
 *
 * Each channel is a 8 bit integer.
 *
 * The first plane usually contains the luma channel. It is mapped
 * into the 2nd channel.
 *
 * The second plane usually contains the first chroma chanel. It is
 * mapped into the 3rd channel.
 *
 * The third plane usually contains the second chroma channel. It is
 * mapped into the 1st channel.
 *
 * Commonly known by the fourcc "YUV444".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G8_R8_B8_444:
 *
 * Multiplane format with 3 planes.
 *
 * Each channel is a 8 bit integer.
 *
 * The first plane usually contains the luma channel. It is mapped
 * into the 2nd channel.
 *
 * The second plane usually contains the second chroma chanel.
 * Subsampled in the X direction. It is mapped into the 1st channel.
 *
 * The third plane usually contains the first chroma channel.
 * Subsampled in the X direction. It is mapped into the 3rd channel.
 *
 * Commonly known by the fourcc "YVU444".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G8B8G8R8_422:
 *
 * Packed format with subsampled channels.
 *
 * Each channel is a 8 bit integer. The red and blue/chroma channels
 * are subsampled and interleaved with the green/luma channel.
 *
 * Each block contains 2 pixels, so the width must be a multiple of
 * 2.
 *
 * Commonly known by the fourcc "YUYV".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G8R8G8B8_422:
 *
 * Packed format with subsampled channels.
 *
 * Each channel is a 8 bit integer. The red and blue/chroma channels
 * are subsampled and interleaved with the green/luma channel.
 *
 * Each block contains 2 pixels, so the width must be a multiple of
 * 2.
 *
 * Commonly known by the fourcc "YVYU".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_R8G8B8G8_422:
 *
 * Packed format with subsampled channels.
 *
 * Each channel is a 8 bit integer. The red and blue/chroma channels
 * are subsampled and interleaved with the green/luma channel.
 *
 * Each block contains 2 pixels, so the width must be a multiple of
 * 2.
 *
 * Commonly known by the fourcc "VYUY".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_B8G8R8G8_422:
 *
 * Packed format with subsampled channels.
 *
 * Each channel is a 8 bit integer. The red and blue/chroma channels
 * are subsampled and interleaved with the green/luma channel.
 *
 * Each block contains 2 pixels, so the width must be a multiple of
 * 2.
 *
 * Commonly known by the fourcc "UYVY".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_X6G10_X6B10_X6R10_420:
 *
 * Multiplane format with 3 planes.
 *
 * Each channel is a 16 bit integer.
 *
 * Only the 10 lower bits are used. The remaining ones must be set to 0 by the
 * producer.
 *
 * The first plane usually contains the luma channel. It is mapped
 * into the 2nd channel.
 *
 * The second plane usually contains the first chroma chanel.
 * Subsampled in both the X and Y direction. It is mapped into the
 * 3rd channel.
 *
 * The third plane usually contains the second chroma channel.
 * Subsampled in both the X and Y direction. It is mapped into the
 * 1st channel.
 *
 * Commonly known by the fourcc "S010".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_X6G10_X6B10_X6R10_422:
 *
 * Multiplane format with 3 planes.
 *
 * Each channel is a 16 bit integer.
 *
 * Only the 10 lower bits are used. The remaining ones must be set to 0 by the
 * producer.
 *
 * The first plane usually contains the luma channel. It is mapped
 * into the 2nd channel.
 *
 * The second plane usually contains the first chroma chanel.
 * Subsampled in the X direction. It is mapped into the 3rd channel.
 *
 * The third plane usually contains the second chroma channel.
 * Subsampled in the X direction. It is mapped into the 1st channel.
 *
 * Commonly known by the fourcc "S210".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_X6G10_X6B10_X6R10_444:
 *
 * Multiplane format with 3 planes.
 *
 * Each channel is a 16 bit integer.
 *
 * Only the 10 lower bits are used. The remaining ones must be set to 0 by the
 * producer.
 *
 * The first plane usually contains the luma channel. It is mapped
 * into the 2nd channel.
 *
 * The second plane usually contains the first chroma chanel. It is
 * mapped into the 3rd channel.
 *
 * The third plane usually contains the second chroma channel. It is
 * mapped into the 1st channel.
 *
 * Commonly known by the fourcc "S410".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_X4G12_X4B12_X4R12_420:
 *
 * Multiplane format with 3 planes.
 *
 * Each channel is a 16 bit integer.
 *
 * Only the 12 lower bits are used. The remaining ones must be set to 0 by the
 * producer.
 *
 * The first plane usually contains the luma channel. It is mapped
 * into the 2nd channel.
 *
 * The second plane usually contains the first chroma chanel.
 * Subsampled in both the X and Y direction. It is mapped into the
 * 3rd channel.
 *
 * The third plane usually contains the second chroma channel.
 * Subsampled in both the X and Y direction. It is mapped into the
 * 1st channel.
 *
 * Commonly known by the fourcc "S012".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_X4G12_X4B12_X4R12_422:
 *
 * Multiplane format with 3 planes.
 *
 * Each channel is a 16 bit integer.
 *
 * Only the 12 lower bits are used. The remaining ones must be set to 0 by the
 * producer.
 *
 * The first plane usually contains the luma channel. It is mapped
 * into the 2nd channel.
 *
 * The second plane usually contains the first chroma chanel.
 * Subsampled in the X direction. It is mapped into the 3rd channel.
 *
 * The third plane usually contains the second chroma channel.
 * Subsampled in the X direction. It is mapped into the 1st channel.
 *
 * Commonly known by the fourcc "S212".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_X4G12_X4B12_X4R12_444:
 *
 * Multiplane format with 3 planes.
 *
 * Each channel is a 16 bit integer.
 *
 * Only the 12 lower bits are used. The remaining ones must be set to 0 by the
 * producer.
 *
 * The first plane usually contains the luma channel. It is mapped
 * into the 2nd channel.
 *
 * The second plane usually contains the first chroma chanel. It is
 * mapped into the 3rd channel.
 *
 * The third plane usually contains the second chroma channel. It is
 * mapped into the 1st channel.
 *
 * Commonly known by the fourcc "S412".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G16_B16_R16_420:
 *
 * Multiplane format with 3 planes.
 *
 * Each channel is a 16 bit integer.
 *
 * The first plane usually contains the luma channel. It is mapped
 * into the 2nd channel.
 *
 * The second plane usually contains the first chroma chanel.
 * Subsampled in both the X and Y direction. It is mapped into the
 * 3rd channel.
 *
 * The third plane usually contains the second chroma channel.
 * Subsampled in both the X and Y direction. It is mapped into the
 * 1st channel.
 *
 * Commonly known by the fourcc "S016".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G16_B16_R16_422:
 *
 * Multiplane format with 3 planes.
 *
 * Each channel is a 16 bit integer.
 *
 * The first plane usually contains the luma channel. It is mapped
 * into the 2nd channel.
 *
 * The second plane usually contains the first chroma chanel.
 * Subsampled in the X direction. It is mapped into the 3rd channel.
 *
 * The third plane usually contains the second chroma channel.
 * Subsampled in the X direction. It is mapped into the 1st channel.
 *
 * Commonly known by the fourcc "S216".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_G16_B16_R16_444:
 *
 * Multiplane format with 3 planes.
 *
 * Each channel is a 16 bit integer.
 *
 * The first plane usually contains the luma channel. It is mapped
 * into the 2nd channel.
 *
 * The second plane usually contains the first chroma chanel. It is
 * mapped into the 3rd channel.
 *
 * The third plane usually contains the second chroma channel. It is
 * mapped into the 1st channel.
 *
 * Commonly known by the fourcc "S416".
 *
 * Since: 4.20
 */
/**
 * GDK_MEMORY_ARGB2101010_PREMULTIPLIED:
 *
 * 4 bytes per pixel
 *
 * Bits 31..30 contain the alpha channel, 29..20 red, 19..10 green
 * and 9..0 blue.
 *
 * The color values are premultiplied with the alpha value.
 *
 * Since: 4.24
 */
/**
 * GDK_MEMORY_ARGB2101010:
 *
 * 4 bytes per pixel
 *
 * Bits 31..30 contain the alpha channel, 29..20 red, 19..10 green
 * and 9..0 blue.
 *
 * Since: 4.24
 */
/**
 * GDK_MEMORY_XRGB2101010:
 *
 * 4 bytes per pixel
 *
 * Bits 31..30 are padding, bits 29..20 contain red, 19..10 green
 * and 9..0 blue.
 *
 * The format is opaque.
 *
 * Since: 4.24
 */
/**
 * GDK_MEMORY_A2B10G10G10_LE_PREMULTIPLIED:
 *
 * 4 bytes per pixel
 *
 * Bits 31..30 contain the alpha channel, 29..20 blue, 19..10 green
 * and 9..0 red.
 *
 * The color values are premultiplied with the alpha value.
 *
 * Since: 4.24
 */
/**
 * GDK_MEMORY_ABGR2101010:
 *
 * 4 bytes per pixel
 *
 * Bits 31..30 contain the alpha channel, 29..20 blue, 19..10 green
 * and 9..0 red.
 *
 * Since: 4.24
 */
/**
 * GDK_MEMORY_ABGR2101010_PREMULTIPLIED:
 *
 * 4 bytes per pixel
 *
 * Bits 31..30 contain the alpha channel, 29..20 blue, 19..10 green
 * and 9..0 red.
 *
 * The color values are premultiplied with the alpha value.
 *
 * Since: 4.24
 */
/**
 * GDK_MEMORY_XBGR2101010:
 *
 * 4 bytes per pixel
 *
 * Bits 31..30 are padding, bits 29..20 contain blue, 19..10 green
 * and 9..0 red.
 *
 * The format is opaque.
 *
 * Since: 4.24
 */
typedef enum {
  GDK_MEMORY_B8G8R8A8_PREMULTIPLIED,
  GDK_MEMORY_A8R8G8B8_PREMULTIPLIED,
  GDK_MEMORY_R8G8B8A8_PREMULTIPLIED,
  GDK_MEMORY_B8G8R8A8,
  GDK_MEMORY_A8R8G8B8,
  GDK_MEMORY_R8G8B8A8,
  GDK_MEMORY_A8B8G8R8,
  GDK_MEMORY_R8G8B8,
  GDK_MEMORY_B8G8R8,
  GDK_MEMORY_R16G16B16,
  GDK_MEMORY_R16G16B16A16_PREMULTIPLIED,
  GDK_MEMORY_R16G16B16A16,
  GDK_MEMORY_R16G16B16_FLOAT,
  GDK_MEMORY_R16G16B16A16_FLOAT_PREMULTIPLIED,
  GDK_MEMORY_R16G16B16A16_FLOAT,
  GDK_MEMORY_R32G32B32_FLOAT,
  GDK_MEMORY_R32G32B32A32_FLOAT_PREMULTIPLIED,
  GDK_MEMORY_R32G32B32A32_FLOAT,
  GDK_MEMORY_G8A8_PREMULTIPLIED GDK_AVAILABLE_ENUMERATOR_IN_4_12,
  GDK_MEMORY_G8A8 GDK_AVAILABLE_ENUMERATOR_IN_4_12,
  GDK_MEMORY_G8 GDK_AVAILABLE_ENUMERATOR_IN_4_12,
  GDK_MEMORY_G16A16_PREMULTIPLIED GDK_AVAILABLE_ENUMERATOR_IN_4_12,
  GDK_MEMORY_G16A16 GDK_AVAILABLE_ENUMERATOR_IN_4_12,
  GDK_MEMORY_G16 GDK_AVAILABLE_ENUMERATOR_IN_4_12,
  GDK_MEMORY_A8 GDK_AVAILABLE_ENUMERATOR_IN_4_12,
  GDK_MEMORY_A16 GDK_AVAILABLE_ENUMERATOR_IN_4_12,
  GDK_MEMORY_A16_FLOAT GDK_AVAILABLE_ENUMERATOR_IN_4_12,
  GDK_MEMORY_A32_FLOAT GDK_AVAILABLE_ENUMERATOR_IN_4_12,
  GDK_MEMORY_A8B8G8R8_PREMULTIPLIED GDK_AVAILABLE_ENUMERATOR_IN_4_14,
  GDK_MEMORY_B8G8R8X8 GDK_AVAILABLE_ENUMERATOR_IN_4_14,
  GDK_MEMORY_X8R8G8B8 GDK_AVAILABLE_ENUMERATOR_IN_4_14,
  GDK_MEMORY_R8G8B8X8 GDK_AVAILABLE_ENUMERATOR_IN_4_14,
  GDK_MEMORY_X8B8G8R8 GDK_AVAILABLE_ENUMERATOR_IN_4_14,
  GDK_MEMORY_G8_B8R8_420 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G8_R8B8_420 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G8_B8R8_422 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G8_R8B8_422 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G8_B8R8_444 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G8_R8B8_444 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G10X6_B10X6R10X6_420 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G12X4_B12X4R12X4_420 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G16_B16R16_420 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G8_B8_R8_410 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G8_R8_B8_410 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G8_B8_R8_411 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G8_R8_B8_411 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G8_B8_R8_420 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G8_R8_B8_420 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G8_B8_R8_422 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G8_R8_B8_422 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G8_B8_R8_444 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G8_R8_B8_444 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G8B8G8R8_422 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G8R8G8B8_422 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_R8G8B8G8_422 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_B8G8R8G8_422 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_X6G10_X6B10_X6R10_420 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_X6G10_X6B10_X6R10_422 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_X6G10_X6B10_X6R10_444 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_X4G12_X4B12_X4R12_420 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_X4G12_X4B12_X4R12_422 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_X4G12_X4B12_X4R12_444 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G16_B16_R16_420 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G16_B16_R16_422 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_G16_B16_R16_444 GDK_AVAILABLE_ENUMERATOR_IN_4_20,
  GDK_MEMORY_ARGB2101010_PREMULTIPLIED GDK_AVAILABLE_ENUMERATOR_IN_4_24,
  GDK_MEMORY_ARGB2101010 GDK_AVAILABLE_ENUMERATOR_IN_4_24,
  GDK_MEMORY_XRGB2101010 GDK_AVAILABLE_ENUMERATOR_IN_4_24,
  GDK_MEMORY_ABGR2101010_PREMULTIPLIED GDK_AVAILABLE_ENUMERATOR_IN_4_24,
  GDK_MEMORY_ABGR2101010 GDK_AVAILABLE_ENUMERATOR_IN_4_24,
  GDK_MEMORY_XBGR2101010 GDK_AVAILABLE_ENUMERATOR_IN_4_24,

  GDK_MEMORY_N_FORMATS
} GdkMemoryFormat;

G_END_DECLS
