// swift-tools-version: 6.1
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "npfoundation",
    products: [
        // Products define the executables and libraries a package produces, making them visible to other packages.
        .library(
            name: "NPFoundation",
            targets: [
                "NPFoundation"
            ]),
        .executable(
            name: "NPFoundationExamples",
            targets: [
                "NPFoundationExamples"
            ])
    ],
    targets: [
        // Targets are the basic building blocks of a package, defining a module or a test suite.
        // Targets can depend on other targets in this package and products from dependencies.
        .target(
            name: "NPFoundation"),
        
        .testTarget(
            name: "NPFoundationTests",
            dependencies: ["NPFoundation"]),
        
        .executableTarget(
            name: "NPFoundationExamples",
            dependencies: ["NPFoundation"]),
    ]
)
