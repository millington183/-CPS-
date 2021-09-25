package com.flushbonading.cps.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.flushbonading.cps.entity.Post;
import com.flushbonading.cps.entity.dto.PostDTO;
import com.flushbonading.cps.mapper.PostMapper;
import com.flushbonading.cps.service.PostService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * <p>
 * 服务实现类
 * </p>
 *
 * @author zyx
 * @since 2021-06-13
 */
@Service
public class PostServiceImpl extends ServiceImpl<PostMapper, Post> implements PostService {

    @Autowired
    PostMapper postMapper;
    
    @Override
    public List<PostDTO> getPostByDepartment(String departmentName) {
        return postMapper.getPostByDepartment(departmentName);
    }
}
