/* source/sgl_conf_template.h
 *
 * MIT License
 *
 * Copyright(c) 2023-present All contributors of SGL  
 *  
 * Email: 1477153217@qq.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// Platform dependent types decelaration.
#ifndef _SIZE_T_DEFINED_
#define _SIZE_T_DEFINED_
typedef unsigned int size_t;
#endif

#define SGL_CONFIG_DEBUG                      0
#define SGL_CONFIG_LOG_LEVEL                  0


//����������TODO
#define SGL_CONFIG_POWERON_ANIM               0

//�������忹�����ȣ�Ĭ�ϲ���4bit�����
#define SGL_CONFIG_FONT_PIXEL_BIT             4


//��ʾ������������ɫ��ȣ�Ĭ��Ϊ32bit
#define SGL_CONFIG_PANEL_PIXEL_DEPTH          16

//FrameBuffer�Ƿ����ڴ�ӳ�䷽ʽ
#define SGL_CONFIG_FRAMEBUFFER_MMAP           0

//Ĭ��page������ɫ
#define SGL_CONFIG_PAGE_COLOR                 SGL_WHITE

//RGB��ɫ����
#define SGL_CONFIG_COLOR16_SWAP               1

//1: standard��ɫ
//2: fast��ɫ
#define SGL_CONFIG_MIXER_TYPE                 2

//0: heap_0
//1: heap_1
//2: heap_2
//3: heap_3
//4: heap_4
//5: heap_tlsf
//6: libc
#define SGL_CONFIG_HEAP_POLICY                5
//�����ڴ�صĴ�С����λKByte
#define SGL_CONFIG_HEAP_POOL_SIZE             32


//�����¼��Ķ������
#define SGL_CONFIG_EVQUEUE_DEPTH              16

//��������Ķ������
#define SGL_CONFIG_TASKQUEUE_DEPTH            8


//�Ƿ���SGL����
#define SGL_CONFIG_FONT_CONSOLAS12            1
#define SGL_CONFIG_FONT_CONSOLAS15            1
#define SGL_CONFIG_FONT_SONG10                1
#define SGL_CONFIG_FONT_SONG23                1
#define SGL_CONFIG_FONT_CASCADIA_MONO17       1

#define SGL_CONFIG_TEXT_UTF8                  0
