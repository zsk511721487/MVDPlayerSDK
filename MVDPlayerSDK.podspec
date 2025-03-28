#
# Be sure to run `pod lib lint MVDPlayerSDK.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'MVDPlayerSDK'
  s.version          = '1.6.3'
  s.summary          = 'A short description of MVDPlayerSDK.'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
TODO: Add long description of the pod here.
                       DESC

  s.homepage         = 'https://github.com/zsk511721487/MVDPlayerSDK'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { '511721487@qq.com' => '511721487@qq.com' }
  s.source           = { :git => 'https://github.com/zsk511721487/MVDPlayerSDK.git', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.platform     = :ios#支持平台

  s.ios.deployment_target = '13.0'
  
  s.ios.vendored_frameworks = "MVDPlayerSDK/frameworks/MVDPlayer.framework"
  
#  s.frameworks = "AVFoundation", "CoreAudio", "CoreGraphics","CoreMedia", "CoreVideo", "Metal", "Security","UIKit", "VideoToolbox"
  
#   s.resource_bundles = {
#     'MVDPlayerSDK' => ["MVDPlayerSDK/frameworks/MVDPlayer.framework"]
#   }

  # s.public_header_files = 'Pod/Classes/**/*.h'
  # s.frameworks = 'UIKit', 'MapKit'
  # s.dependency 'AFNetworking', '~> 2.3'
end
