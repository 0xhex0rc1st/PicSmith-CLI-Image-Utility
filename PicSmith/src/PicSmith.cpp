// ...existing code...
int compression_value = 0;
int target_width = 0;
int target_height = 0;
// ...existing code...
else if(arg == "-c") {
    arg_c = true;
    if(!arg_f) {
        std::filesystem::path input_path(input_image_path);
        format = input_path.extension().string();
        if(!format.empty() && format[0] == '.') {
            format.erase(0, 1);
        }
        format = toLower(format);
    }

    if(format == "webp") {
        if(i + 1 < argc) {
            std::string value = argv[++i];
            for(char c : value) {
                if(!isdigit(c)) {
                    std::cerr << "[!]Error: compression value must a number\n";
                    return 1;
                }
            }
            compression_value = std::stoi(value);   
            if(compression_value < 1 || compression_value > 100) {
                std::cerr << "[!]Error: compression value must be between 1-100\n";
                return 1;
            }                                     
        }
        else {
            compression_value = 80;
        }
    }
    else if(format == "png") {
        if(i + 1 < argc) {
            std::string value = argv[++i];
            for(char c : value) {
                if(!isdigit(c)) {
                    std::cerr << "[!]Error: compression value must a number\n";
                    return 1;
                }
            }
            compression_value = std::stoi(value);
            if(compression_value < 1 || compression_value > 9) {
                std::cerr << "[!]Error: compression value must be between 1-9\n";
                return 1;
            }   
        }
        else {
            compression_value = 6;
        }
    }
    else if(format == "jpeg" || format == "jpg") {
        if(i + 1 < argc) {
            std::string value = argv[++i];
            for(char c : value) {
                if(!isdigit(c)) {
                    std::cerr << "[!]Error: compression value must a number\n";
                    return 1;
                }
            }
            compression_value = std::stoi(value);
            if(compression_value < 1 || compression_value > 100) {
                std::cerr << "[!]Error: compression value must be between 1-100\n";
                return 1;
            }
        }
        else {
            compression_value = 85;
        }
    }
    else {
        std::cerr << "[!]Error: compression is not supported for this format\n";
        return 1;
    }
}
// ...existing code...
else if(arg == "-r") {
    arg_r = true;
    if(!arg_f) {
        std::filesystem::path input_path(input_image_path);
        format = input_path.extension().string();
        if(!format.empty() && format[0] == '.') {
            format.erase(0, 1);
        }
        format = toLower(format);
    }
    if(i + 1 < argc) {
        std::string res_key = argv[++i];
        res_key = toLower(res_key);
        bool found = false;
        // پشتیبانی از فرمت WxH
        size_t x_pos = res_key.find('x');
        if(x_pos != std::string::npos) {
            std::string w = res_key.substr(0, x_pos);
            std::string h = res_key.substr(x_pos + 1);
            if(std::all_of(w.begin(), w.end(), ::isdigit) && std::all_of(h.begin(), h.end(), ::isdigit)) {
                target_width = std::stoi(w);
                target_height = std::stoi(h);
                found = true;
            }
        }
        if(!found) {
            for(const auto& kv : predefined_resolutions) {
                std::string key_lower = toLower(kv.first);
                if(key_lower == res_key) {
                    target_width = kv.second.width;
                    target_height = kv.second.height;
                    found = true;
                    break;
                }
            }
        }
        if(!found) {
            std::cerr << "[!]Error: invalid resolution key or format '" << res_key << "'\n";
            std::cerr << "Valid options: SD, SD_640x480, SD_800x600, HD, HD_widescreen, HD+, FHD, 2K, QHD, 4K, 8K or WxH\n";
            return 1;
        }
    } 
    else {
        std::cerr << "[!]Error: missing argument for -r\n";
        return 1;
    }
}
// ...existing code...
bool success;
if (!compression_params.empty()) {
    success = cv::imwrite(outpath, image_to_save, compression_params);
} 
else {
    success = cv::imwrite(outpath, image_to_save);
}
if (!success) {
    std::cerr << "[!]Error: failed to save image to " << outpath << "\n";
    return 1;
}
// ...existing code...
