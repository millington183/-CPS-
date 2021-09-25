package com.flushbonading.cps.controller;


import com.alibaba.fastjson.JSON;
import com.flushbonading.cps.entity.dto.PostDTO;
import com.flushbonading.cps.service.PostService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

/**
 * <p>
 * 前端控制器
 * </p>
 *
 * @author zyx
 * @since 2021-06-13
 */
@RestController
@RequestMapping("/api/post")
@Api(tags = "职务模块", value = "职务模块")
public class PostController {
    @Autowired
    PostService postService;
    @Autowired
    RedisTemplate<String, Object> redisTemplate;

    @ApiOperation("根据部门查询底下所有职务")
    @GetMapping("/all/{departmentName}")
    public String getPostByDepartment(@PathVariable("departmentName") String departmentName) {
        //在这里做缓存
        List<PostDTO> posts = (List<PostDTO>) redisTemplate.opsForValue().get("post:" + departmentName);
        if (posts != null) {
            return JSON.toJSONString(posts);
        }
        posts = postService.getPostByDepartment(departmentName);
        redisTemplate.opsForValue().set("post:" + departmentName, posts);
        return JSON.toJSONString(posts);
    }
}

