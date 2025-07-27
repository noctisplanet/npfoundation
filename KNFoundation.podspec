Pod::Spec.new do |spec|
    spec.name                           = 'KNFoundation'
    spec.version                        = '0.1.0'
    spec.license                        = { :type => 'MIT', :file => 'LICENSE' }
    spec.homepage                       = 'https://github.com/nextpangea/npfoundation'
    spec.authors                        = { 'Jonathan Lee' => 'Jonathan.Kaishan@gmail.com' }
    spec.summary                        = 'Extensions SDK for iOS and macOS.'
    spec.source                         = { :git => 'https://github.com/nextpangea/npfoundation.git', :tag => spec.version.to_s }

    spec.ios.deployment_target          = '12.2'
    spec.osx.deployment_target          = '11.0'
    spec.watchos.deployment_target      = '11.0'
    spec.tvos.deployment_target         = '12.2'
    spec.visionos.deployment_target     = '1.0'

    spec.static_framework = true
    spec.frameworks                     = 'Foundation'

    spec.source_files                   = 'Sources/KNFoundation/**/*.{h,c,m}'
    spec.public_header_files            = 'Sources/KNFoundation/include/**/*.{h}'
    spec.module_map                     = 'Sources/KNFoundation/KNFoundation.modulemap'
end
