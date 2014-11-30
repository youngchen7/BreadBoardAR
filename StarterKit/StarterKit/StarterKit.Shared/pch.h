#pragma once

#include <wrl.h>
#include <wrl/client.h>
#include <d3d11_2.h>
#include <d2d1_2.h>
#include <d2d1effects_1.h>
#include <dwrite_2.h>
#include <wincodec.h>
#include <DirectXColors.h>
#include <DirectXMath.h>
#include <memory>
#include <agile.h>
#include <concrt.h>
#include <collection.h>
#include "App.xaml.h"

#include <ppltasks.h>

#include <wrl\implements.h>
#include <wrl\wrappers\corewrappers.h>

#include <queue>
#include <sstream>

#include <robuffer.h>

#include <mfapi.h>
#include <mfidl.h>
#include <Mferror.h>

#include <windows.media.h>
#include <windows.media.mediaproperties.h>

namespace AWM = ::ABI::Windows::Media;
namespace AWMMp = ::ABI::Windows::Media::MediaProperties;
namespace AWFC = ::ABI::Windows::Foundation::Collections;
namespace MW = ::Microsoft::WRL;
namespace MWD = ::Microsoft::WRL::Details;
namespace MWW = ::Microsoft::WRL::Wrappers;
namespace WMC = ::Windows::Media::Capture;
namespace WF = ::Windows::Foundation;
namespace WMMp = ::Windows::Media::MediaProperties;
namespace WSS = ::Windows::Storage::Streams;