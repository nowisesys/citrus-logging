<?php

// Copyright (C) 2019 Anders Lövgren (Nowise Systems)
//
// This library is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library. If not, see <http://www.gnu.org/licenses/>.

// 
// Simple PHP script for debugging the HTTP/HTTPS target (http.cpp). Copy
// this file to your public HTML root. 
// 
// For testing the script from command line:
// bash$> curl -XPOST http://localhost/http.php -d '{"test":"works"}'
// 

error_log(trim(file_get_contents("php://input")));
